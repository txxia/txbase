#include "txbase/stdafx.h"
#include "fontmap.h"
#include "fonts/droid_sans.h"
#include "txbase/sys/memory.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "txbase/libs/stb_truetype.h"

namespace TX {
	float GlyphPosMap::GetWidth(int index, int count) const {
		int max = map.size() - 1;
		if (max <= 0) return 0.f;
		int begin = Math::Clamp(index, 0, max);
		int end = Math::Clamp(index + count, 0, max);
		return begin == end ? 0.f : map[end] - map[begin];
	}

	int GlyphPosMap::GetIndex(float offset) const {
		auto ceiling = std::lower_bound(map.begin(), map.end(), offset);
		if (ceiling != map.begin() && ceiling != map.end()) {
			return (*ceiling - offset) < (offset - *(ceiling - 1)) ?
				(ceiling - map.begin()) :
				(ceiling - 1 - map.begin());
		}
		else {
			return Math::Clamp(
				int(ceiling - map.begin()),
				0,
				int(map.size() - 1));
		}
	}

	void GlyphPosMap::Recalculate(const FontMap *font, const std::string& text) {
		Clear();
		Vec2 pos;
		map.reserve(text.length() + 1);

		for (const char& c : text) {
			font->GetChar(c, pos, nullptr, nullptr, this);
		}
	}

	FontMap::FontMap() {
		// initialize font texture
		glGenTextures(1, &texID_);
		data_ = new stbtt_bakedchar[96];	// ASCII 32..126;
	}
	FontMap::~FontMap() {
		glDeleteTextures(1, &texID_);
		MemDeleteArray<stbtt_bakedchar>(data_);
	}

	void FontMap::LoadFile(const std::string& file, float height) {
		std::ifstream in(file, std::ifstream::ate | std::ifstream::binary);
		if (in.is_open()) {
			std::streampos size = in.tellg();
			char *buf = new char[static_cast<size_t>(size)];
			AutoDeleteArray<char> _(buf);
			in.seekg(0, std::ios::beg);
			in.read(buf, size);
			in.close();
			Load(reinterpret_cast<unsigned char*>(buf), height);
		}
		else {
			throw "failed to open file: " + std::string(file);
		}
	}

	void FontMap::Load(const unsigned char *buf, float height) {
		fontHeight_ = height;
		unsigned char tempBitmap[bitmapSize * bitmapSize];
		int res = stbtt_BakeFontBitmap(buf, 0, height, tempBitmap, bitmapSize, bitmapSize, 32, 96, reinterpret_cast<stbtt_bakedchar*>(data_));
		if (res > 0) {
			glBindTexture(GL_TEXTURE_2D, texID_);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, bitmapSize, bitmapSize, 0, GL_ALPHA, GL_UNSIGNED_BYTE, tempBitmap);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else {
			throw "failed to load font: " + res;
		}
	}

	void FontMap::LoadDefault() {
		Load(DroidSans_ttf, 14.f);
	}

	bool FontMap::GetChar(const char& ch, Vec2& pos, Rect *rect, Rect *uv, GlyphPosMap *posMap) const {
		if (ch >= 32 && ch < 128) {
			float left = pos.x;
			stbtt_aligned_quad q;
			stbtt_GetBakedQuad(reinterpret_cast<stbtt_bakedchar*>(data_),
				bitmapSize, bitmapSize,
				ch - 32, &pos.x, &pos.y, &q, 1);
			if (posMap)
				posMap->Append(pos.x - left);
			if (uv) {
				uv->min.x = q.s0; uv->min.y = q.t0;
				uv->max.x = q.s1; uv->max.y = q.t1;
			}
			if (rect) {
				rect->min.x = q.x0; rect->min.y = q.y0;
				rect->max.x = q.x1; rect->max.y = q.y1;
			}
			return true;
		}
		else {
			return false;
		}
	}
	float FontMap::GetWidth(char c) const {
		Rect r; Vec2 pos;
		if (GetChar(c, pos, &r)) {
			return pos.x;
		}
		else {
			return 0.f;
		}
	}
	float FontMap::GetWidth(const std::string& str) const {
		Vec2 pos;
		for (const char& c : str) {
			GetChar(c, pos, nullptr);
		}
		return pos.x;
	}
}

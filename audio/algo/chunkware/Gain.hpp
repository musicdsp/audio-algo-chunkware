/**
 * @author Bojan MARKOVIC
 * @author Edouard DUPIN
 * @copyright 2006, ChunkWare Music Software, OPEN-SOURCE
 * @license BSD-1 (see license file)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#pragma once

#include <etk/types.hpp>

namespace audio {
	namespace algo {
		namespace chunkware {
			// linear -> dB conversion
			static inline double lin2dB(double _lin) {
				static const double LOG_2_DB = 8.6858896380650365530225783783321;	// 20 / ln(10)
				return log(_lin) * LOG_2_DB;
			}
			// dB -> linear conversion
			static inline double dB2lin(double _dB) {
				static const double DB_2_LOG = 0.11512925464970228420089957273422;	// ln(10) / 20
				return exp(_dB * DB_2_LOG);
			}
		}
	}
}


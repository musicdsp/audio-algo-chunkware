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


#ifndef __AUDIO_ALGO_CHUNKWARE_COMPRESSOR_RMS_H__
#define __AUDIO_ALGO_CHUNKWARE_COMPRESSOR_RMS_H__

#include "Compressor.h"

namespace audio {
	namespace algo {
		namespace chunkware {
			class CompresssorRms : public Compresssor {
				public:
					CompresssorRms();
					virtual ~CompresssorRms() {}
					// sample rate
					virtual void setSampleRate(double sampleRate);
					// RMS window
					virtual void setWindow(double ms);
					virtual double getWindow() const { return ave_.getTc(); }
					// runtime process
					virtual void initRuntime();			// call before runtime (in resume())
					void process(double &in1, double &in2);	// compressor runtime process
				protected:
					EnvelopeDetector ave_; //!< averager
					double aveOfSqrs_; //!< average of squares
			};
		}
	}
}

#endif

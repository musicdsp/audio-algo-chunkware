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


#ifndef __AUDIO_ALGO_CHUNKWARE_ATT_REL_ENVELOPE_H__
#define __AUDIO_ALGO_CHUNKWARE_ATT_REL_ENVELOPE_H__

#include "EnvelopeDetector.h"

namespace audio {
	namespace algo {
		namespace chunkware {
			//-------------------------------------------------------------
			// attack/release envelope
			//-------------------------------------------------------------
			class AttRelEnvelope {
				public:
					AttRelEnvelope(double att_ms = 10.0,
					               double rel_ms = 100.0,
					               double sampleRate = 44100.0);
					virtual ~AttRelEnvelope() {}
					// attack time constant
					virtual void   setAttack(double ms);
					virtual double getAttack() const {
						return att_.getTc();
					}
					// release time constant
					virtual void   setRelease(double ms);
					virtual double getRelease() const {
						return rel_.getTc();
					}
					// sample rate dependencies
					virtual void   setSampleRate(double sampleRate);
					virtual double getSampleRate() const {
						return att_.getSampleRate();
					}
					// runtime function
					void run(double in, double &state) {
						/* assumes that:
						* positive delta = attack
						* negative delta = release
						* good for linear & log values
						*/
						if (in > state) {
							// attack
							att_.run(in, state);
						} else {
							// release
							rel_.run(in, state);
						}
					}
				private:
					EnvelopeDetector att_;
					EnvelopeDetector rel_;
			};
		}
	}
}

#endif

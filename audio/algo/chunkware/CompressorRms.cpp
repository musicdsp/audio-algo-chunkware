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


#include <audio/algo/chunkware/CompressorRms.hpp>


audio::algo::chunkware::CompressorRms::CompressorRms() :
  m_averager(5.0),
  m_averageSuares(DC_OFFSET) {
	
}

void audio::algo::chunkware::CompressorRms::setSampleRate(double _sampleRate) {
	audio::algo::chunkware::Compressor::setSampleRate(_sampleRate);
	m_averager.setSampleRate(_sampleRate);
}

void audio::algo::chunkware::CompressorRms::setWindow(double _ms) {
	m_averager.setTc(_ms);
}

void audio::algo::chunkware::CompressorRms::initRuntime() {
	audio::algo::chunkware::Compressor::initRuntime();
	m_averageSuares = DC_OFFSET;
}

void audio::algo::chunkware::CompressorRms::processDouble(double* _out, const double* _in, int8_t _nbChannel) {
	double sum = 0.0;
	// create sidechain
	for (int8_t iii=0; iii<_nbChannel; ++iii) {
		sum += _in[iii] * _in[iii]; // square input
	}
	sum += DC_OFFSET; // DC offset, to prevent denormal
	m_averager.run(sum, m_averageSuares); // average of squares
	double rms = sqrt(m_averageSuares); // rms (sort of ...)
	/* REGARDING THE RMS AVERAGER: Ok, so this isn't a REAL RMS
	 * calculation. A true RMS is an FIR moving average. This
	 * approximation is a 1-pole IIR. Nonetheless, in practice,
	 * and in the interest of simplicity, this method will suffice,
	 * giving comparable results.
	 */
	// rest of process
	processDouble(_out, _in, _nbChannel, rms);
}

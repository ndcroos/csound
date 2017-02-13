/*
  plugin.h
  CPOF Csound Plugin Opcode Framework
  C++ plugin opcode interface

  (c) Victor Lazzarini, 2017

  This file is part of Csound.

  The Csound Library is free software; you can redistribute it
  and/or modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  Csound is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with Csound; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
  02111-1307 USA

*/

#ifndef _PLUGIN_H_
#define _PLUGIN_H_
#include <algorithm>
#include <complex>
#include <csdl.h>
#include <pstream.h>
#include <iostream>

namespace csnd {

/** opcode threads: i-time, k-perf and/or a-perf
*/
enum thread { i = 1, k = 2, ik = 3, a = 4, ia = 5, ika = 7 };

/** fsig formats: phase vocoder, stft polar, stft complex, or
    sinusoidal tracks
*/
enum fsig_format { pvs = 0, polar, complex, tracks };

/** Csound Engine object.
 */
class Csound : CSOUND {

  /** Utility classes
   */
  template <typename T> friend class Vector;
  friend class Fsig;
  friend class Table;
  template <typename T> friend class AuxMem;

  /**
    @private
    opcode function template (deinit-time)
   */
  template <typename T> static int deinit(CSOUND *csound, void *p) {
    return ((T *)p)->deinit();
  }

public:
  /** init-time error message
   */
  int init_error(const std::string &s) {
    return InitError(this, "%s\n", s.c_str());
  }

  /** perf-time error message
   */
  int perf_error(const std::string &s, INSDS *inst) {
    return PerfError(this, inst, "%s\n", s.c_str());
  }

  /** warning message
   */
  void warning(const std::string &s) { Warning(this, "%s", s.c_str()); }

  /** console messages
   */
  void message(const std::string &s) { Message(this, "%s\n", s.c_str()); }

  /** system sampling rate
   */
  MYFLT sr() { return GetSr(this); }

  /** system max amp reference
   */
  MYFLT _0dbfs() { return Get0dBFS(this); }

  /** system A4 reference
   */
  MYFLT _A4() { return GetA4(this); }

  /** number of audio channels (out)
   */
  uint32_t nchnls() { return GetNchnls(this); }

  /** number of audio channels (in)
   */
  uint32_t nchnls_i() { return GetNchnls_i(this); }

  /** time count (samples)
   */
  int64_t current_time_samples() { return GetCurrentTimeSamples(this); }

  /** time count (seconds)
   */
  double current_time_seconds() {
    return GetCurrentTimeSamples(this) / GetSr(this);
  }

  /** midi channel number for this instrument
   */
  int midi_channel() { return GetMidiChannelNumber(this); }

  /** midi note number for this instrument
   */
  int midi_note_num() { return GetMidiNoteNumber(this); }

  /** midi note velocity for this instrument
   */
  int midi_note_vel() { return GetMidiVelocity(this); }

  /** midi aftertouch for this channel
   */
  MYFLT midi_chn_aftertouch() { return GetMidiChannel(this)->aftouch; }

  /** midi poly aftertouch for this channel
   */
  MYFLT midi_chn_polytouch(uint32_t note) {
    return GetMidiChannel(this)->polyaft[note];
  }

  /** midi ctl change for this channel
   */
  MYFLT midi_chn_ctl(uint32_t ctl) {
    return GetMidiChannel(this)->ctl_val[ctl];
  }

  /** midi pitchbend for this channel
   */
  MYFLT midi_chn_pitchbend() { return GetMidiChannel(this)->pchbend; }

  /** list of active instrument instances for this channel \n
      returns an INSDS array with 128 items, one per
      MIDI note number. Inactive instances are marked NULL.
   */
  const INSDS *midi_chn_list() {
    return (const INSDS *)GetMidiChannel(this)->kinsptr;
  }

  /** deinit registration for a given plugin class
   */
  template <typename T> void plugin_deinit(T *p) {
    RegisterDeinitCallback(this, (void *)p, deinit<T>);
  }

  /** FFT setup: real-to-complex and complex-to-real \n
      direction: FFT_FWD or FFT_INV \n
      returns a handle to the FFT setup.
   */
  void *rfft_setup(uint32_t size, uint32_t direction) {
    return RealFFT2Setup(this, size, direction);
  }

  /** FFT operation, in-place, but also
      returning a pointer to std::complex<MYFLT>
      to the transformed data memory.
  */
  std::complex<MYFLT> *rfft(void *setup, MYFLT *data) {
    RealFFT2(this, setup, data);
    return reinterpret_cast<std::complex<MYFLT> *>(data);
  }
};

/** One-dimensional array container
    template class
 */
template <typename T> class Vector : ARRAYDAT {
  
public:
  /** Initialise the container
   */
  void init(Csound *csound, int size) {
    if (data == NULL || dimensions == 0 ||
        (dimensions == 1 && sizes[0] < size)) {
      size_t ss;
      if (data == NULL) {
        CS_VARIABLE *var = arrayType->createVariable(csound, NULL);
        arrayMemberSize = var->memBlockSize;
      }
      ss = arrayMemberSize * size;
      if (data == NULL)
        data = (MYFLT *)csound->Calloc(csound, ss);
      else
        data = (MYFLT *)csound->ReAlloc(csound, data, ss);
      dimensions = 1;
      sizes = (int *)csound->Malloc(csound, sizeof(int));
      sizes[0] = size;
    }
  }

  /** iterator type
   */
  typedef T *iterator;

  /** const_iterator type
  */
  typedef const T *const_iterator;

  /** vector beginning
   */
  iterator begin() { return (T *)data; }

  /** vector end
   */
  iterator end() { return (T *) ((char*)data + sizes[0]*arrayMemberSize); }

  /** array subscript access (write)
   */
  T &operator[](int n) { return ((T *)data)[n]; }

  /** array subscript access (read)
   */
  const T &operator[](int n) const { return ((T *)data)[n]; }

  /** array subscript access (read)
   */
  uint32_t len() { return sizes[0]; }

  /** element offset 
   */
  uint32_t elem_offset() { return arrayMemberSize/sizeof(T); }

  /** array data
   */
  T *data_array() { return (T *)data; }
};

typedef std::complex<float> pvscmplx;
typedef std::complex<MYFLT> sldcmplx;

/** PvBin holds one Phase Vocoder bin
 */
template <typename T> class PvBin {
  T am;
  T fr;

public:
  /** constructor
   */
  PvBin() : am((T)0), fr((T)0){};

  /** access amplitude
   */
  T amp() { return am; }

  /** access frequency
   */
  T freq() { return fr; }

  /** set amplitude
   */
  T amp(float a) { am = a; }

  /** set frequency
   */
  T freq(float f) { fr = f; }

  /** multiplication (unary)
   */
  const PvBin &operator*=(const PvBin &bin) {
    am *= bin.am;
    fr = bin.fr;
    return *this;
  }

  /** multiplication (binary)
   */
  PvBin operator*(const PvBin &a) {
    PvBin res = *this;
    return (res *= a);
  }

  /** multiplication by MYFLT (unary)
   */
  const PvBin &operator*=(MYFLT f) {
    am *= f;
    return *this;
  }

  /** multiplication by MYFLT (binary)
   */
  PvBin operator*(MYFLT f) {
    PvBin res = *this;
    return (res *= f);
  }

  /** cast to std::complex<T>&
   */
  operator pvscmplx &() { return (pvscmplx &)reinterpret_cast<T(&)[2]>(*this); }

  /** cast to std::complex<T>*
   */
  operator pvscmplx *() { return (pvscmplx *)reinterpret_cast<T *>(this); }
};

/** Phase Vocoder bin */
typedef PvBin<float> pv_bin;

/** Sliding Phase Vocoder bin */
typedef PvBin<MYFLT> spv_bin;

template <typename T> class Pvs;

/** Phase Vocoder frame */
typedef Pvs<pv_bin> pv_frame;

/** Sliding Phase Vocoder frame */
typedef Pvs<spv_bin> spv_frame;

/** fsig base class, holds PVSDAT data
 */
class Fsig : protected PVSDAT {
public:
  /** initialise the object, allocating memory
      if necessary.
   */
  void init(Csound *csound, int32_t n, int32_t h, int32_t w, int32_t t,
            int32_t f, int32_t nb = 0, int32_t sl = 0, uint32_t nsmps = 1) {
    N = n;
    overlap = h;
    winsize = w;
    wintype = t;
    format = f;
    NB = nb;
    sliding = sl;
    if (!sliding) {
      int bytes = (n + 2) * sizeof(float);
      if (frame.auxp == nullptr || frame.size < bytes) {
        csound->AuxAlloc(csound, bytes, &frame);
        std::fill((float *)frame.auxp, (float *)frame.auxp + n + 2, 0);
      }
    } else {
      int bytes = (n + 2) * sizeof(MYFLT) * nsmps;
      if (frame.auxp == NULL || frame.size < bytes)
        csound->AuxAlloc(csound, bytes, &frame);
    }
    framecount = 1;
  }
  void init(Csound *csound, const Fsig &f, uint32_t nsmps = 1) {
    init(csound, f.N, f.overlap, f.winsize, f.wintype, f.format, f.NB,
         f.sliding, nsmps);
  }

  /** get the DFT size
   */
  uint32_t dft_size() { return N; }

  /** get the analysis hop size
   */
  uint32_t hop_size() { return overlap; }

  /** get the analysis window size
   */
  uint32_t win_size() { return winsize; }

  /** get the window type
   */
  int32_t win_type() { return wintype; }

  /** get the number of bins
   */
  uint32_t nbins() { return N / 2 + 1; }

  /** get the framecount
   */
  uint32_t count() const { return framecount; }

  /** set framecount
   */
  uint32_t count(uint32_t cnt) { return (framecount = cnt); }

  /** check for sliding mode
   */
  bool isSliding() { return (bool)sliding; }

  /** get fsig data format
   */
  int fsig_format() { return format; }

  /** convert to pv_frame ref
   */
  operator pv_frame &() { return reinterpret_cast<pv_frame &>(*this); }

  /** convert to spv_frame ref
   */
  operator spv_frame &() { return reinterpret_cast<spv_frame &>(*this); }
};

/**  Container class for a Phase Vocoder
     analysis frame
*/
template <typename T> class Pvs : public Fsig {

public:
  /** iterator type
  */
  typedef T *iterator;

  /** const_iterator type
  */
  typedef const T *const_iterator;

  /** returns an iterator to the
      beginning of the frame
   */
  iterator begin() { return (T *)frame.auxp; }

  /** returns an iterator to the
       end of the frame
    */
  iterator end() { return (T *)frame.auxp + N / 2 + 1; }

  /** array subscript access operator (write)
   */
  T &operator[](int n) { return ((T *)frame.auxp)[n]; }

  /** array subscript access operator (read)
   */
  const T &operator[](int n) const { return ((T *)frame.auxp)[n]; }

  /** frame data pointer
   */
  T *data() const { return (T *)frame.auxp; }

  /** return the container length
   */
  uint32_t len() { return nbins(); }
};

/** function table container class
 */
class Table : FUNC {

public:
  /** Initialise this object from an opcode
      argument arg */
  int init(Csound *csound, MYFLT *arg) {
    Table *f = (Table *)csound->FTnp2Find(csound, arg);
    if (f != nullptr) {
      std::copy(f, f + 1, this);
      return OK;
    }
    return NOTOK;
  }

  /** iterator type
  */
  typedef MYFLT *iterator;

  /** const_iterator type
  */
  typedef const MYFLT *const_iterator;

  /** returns an iterator to the
      beginning of the table
   */
  iterator begin() { return ftable; }

  /** returns an iterator to the
       end of the table
    */
  iterator end() { return ftable + flen; }

  /** array subscript access operator (write)
   */
  MYFLT &operator[](int n) { return ftable[n]; }

  /** array subscript access operator (read)
   */
  const MYFLT &operator[](int n) const { return ftable[n]; }

  /** function table data pointer
   */
  MYFLT *data() const { return ftable; }

  /** function table length
   */
  uint32_t len() { return flen; }
};

/** vector container template using Csound AuxAlloc
    mechanism for dynamic memory allocation
 */
template <typename T> class AuxMem : AUXCH {

public:
  /** allocate memory for the container
   */
  void allocate(Csound *csound, int n) {
    int bytes = n * sizeof(T);
    if (auxp == nullptr || size < bytes) {
      csound->AuxAlloc(csound, bytes, (AUXCH *)this);
      std::fill((T *)auxp, (T *)auxp + n, 0);
    }
  }

  /** iterator type
  */
  typedef T *iterator;

  /** const_iterator type
  */
  typedef const T *const_iterator;

  /** vector beginning
   */
  iterator begin() { return (T *)auxp; }

  /** vector end
   */
  iterator end() { return (T *)endp; }

  /** array subscript access (write)
   */
  T &operator[](int n) { return ((T *)auxp)[n]; }

  /** array subscript access (read)
   */
  const T &operator[](int n) const { return ((T *)auxp)[n]; }

  /** returns a pointer to the vector data
   */
  T *data() { return (T *)auxp; }

  /** returns the length of the vector
   */
  uint32_t len() { return size / sizeof(T); }
};

/** Parameters template class
 */
template <uint32_t N> class Params {
  MYFLT *ptrs[N];

public:
  /** parameter access via array subscript (write)
   */
  MYFLT &operator[](int n) { return *ptrs[n]; }

  /** parameter access via array subscript (read)
   */
  const MYFLT &operator[](int n) const { return *ptrs[n]; }

  /** parameter data (MYFLT pointer) at index n
   */
  MYFLT *data(int n) { return ptrs[n]; }

  /** parameter string data (STRINGDAT ref) at index n
   */
  STRINGDAT &str_data(int n) { return (STRINGDAT &)*ptrs[n]; }

  /** parameter fsig data (Fsig ref) at index n
   */
  Fsig &fsig_data(int n) { return (Fsig &)*ptrs[n]; }

  /** 1-D array data as Vector template ref
   */
  template <typename T> Vector<T> &vector_data(int n) {
    return (Vector<T> &)*ptrs[n];
  }
};

/** Plugin template base class:
    N outputs and M inputs
 */
template <uint32_t N, uint32_t M> struct Plugin : OPDS {
  /** output arguments */
  Params<N> outargs;
  /** input arguments */
  Params<M> inargs;
  /** Csound engine */
  Csound *csound;
  /** sample-accurate offset */
  uint32_t offset;
  /** vector samples to process */
  uint32_t nsmps;

  /** i-time function placeholder
   */
  int init() { return OK; }

  /** k-rate function placeholder
   */
  int kperf() { return OK; }

  /** a-rate function placeholder
   */
  int aperf() { return OK; }

  /** sample-accurate offset for
      a-rate opcodes; updates offset
      and nsmps
   */
  void sa_offset(MYFLT *v) {
    uint32_t early = insdshead->ksmps_no_end;
    nsmps = insdshead->ksmps - early;
    offset = insdshead->ksmps_offset;
    if (UNLIKELY(offset))
      std::fill(v, v + offset, 0);
    if (UNLIKELY(early))
      std::fill(v + nsmps, v + nsmps + early, 0);
  }
};

/** Fsig plugin template base class:
    N outputs and M inputs
 */
template <uint32_t N, uint32_t M> struct FPlugin : Plugin<N, M> {
  /** current frame time index */
  uint32_t framecount;
};

/**
  @private
  opcode thread function template (i-time)
*/
template <typename T> int init(CSOUND *csound, T *p) {
  p->csound = (Csound *)csound;
  return p->init();
}

/**
   @private
   opcode thread function template (k-rate)
*/
template <typename T> int kperf(CSOUND *csound, T *p) {
  p->csound = (Csound *)csound;
  return p->kperf();
}

/**
  @private
  opcode thread function template (a-rate)
*/
template <typename T> int aperf(CSOUND *csound, T *p) {
  p->csound = (Csound *)csound;
  return p->aperf();
}

/** plugin registration function template
 */
template <typename T>
int plugin(CSOUND *csound, const char *name, const char *oargs,
           const char *iargs, uint32_t thread, uint32_t flags = 0) {
  return csound->AppendOpcode(csound, (char *)name, sizeof(T), flags, thread,
                              (char *)oargs, (char *)iargs, (SUBR)init<T>,
                              (SUBR)kperf<T>, (SUBR)aperf<T>);
}

/** plugin registration function template
    for classes with self-defined opcode argument types
 */
template <typename T>
int plugin(CSOUND *csound, const char *name, uint32_t thread,
           uint32_t flags = 0) {
  return csound->AppendOpcode(csound, (char *)name, sizeof(T), 0, thread,
                              (char *)T::otypes, (char *)T::itypes,
                              (SUBR)init<T>, (SUBR)kperf<T>, (SUBR)aperf<T>);
}

/** Plugin library entry point
 */
void on_load(CSOUND *);

}

/**
  @private
  library loading functions
*/
extern "C" {
PUBLIC int csoundModuleCreate(CSOUND *csound) { return 0; }
PUBLIC int csoundModuleDestroy(CSOUND *csound) { return 0; }
PUBLIC int csoundModuleInit(CSOUND *csound) {
  csnd::on_load(csound);
  return 0;
  }
}
#endif

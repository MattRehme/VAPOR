#ifndef _MatWaveBase_h_
#define _MatWaveBase_h_

#include <string>
#include "WaveFiltBase.h"

using namespace std;

namespace VAPoR {

//
//! \class MatWaveBase
//! \brief A base class for a Matlab-like wavelet bank
//! \author John Clyne
//! \version $Revision$
//! \date    $Date$
//!
//! The MatWaveBase class is a base class for building Matlab-inspired
//! wavelet filter banks. In many cases the methods provided behave
//! similarly - in some cases indentically - to the Matlab Wavelet Toolbox
//! version 4 command of the same name.
//!
class WASP_API MatWaveBase : public Wasp::MyBase {

  public:
    //! \enum dwtmode_t
    //! Enumerated boundary extension modes
    //!
    enum dwtmode_t { INVALID = -1, ZPD, SYMH, SYMW, ASYMH, ASYMW, SP0, SP1, PPD, PER };

    //! Create a wavelet filter bank
    //!
    //! \param[in] wname Name of wavelet.
    //! \param[in] mode The boundary extension mode.
    //!
    //! \sa dwtmode()
    //!
    MatWaveBase(const string &wname, const string &mode);
    MatWaveBase(const string &wname);
    virtual ~MatWaveBase();

    //! Set the discrete wavelet extension transform mode
    //!
    //! \param[in] mode Valid values for mode are: "zpd", "symh", "symw",
    //! "asymh", "asymw", "sp0", "sp1",
    //! "spd", "ppd", and "per".
    //!
    //! \retval status a non-negative int is returned on success
    //!
    int dwtmode(const string &mode);

    //! Set the discrete wavelet extension transform mode
    //!
    //! \param[in] mode
    //!
    //! \retval status a non-negative int is returned on success
    //! \sa dwtmode_t
    //!
    int dwtmode(dwtmode_t mode);

    //! Get the current discrete wavelet extension transform mode
    //!
    //! \param[out] mode Current mode
    //!
    //! \retval status a non-negative int is returned on success
    //!
    const string dwtmode() const;

    //! Get the current discrete wavelet extension transform mode
    //!
    //! \retval mode
    //!
    dwtmode_t dwtmodeenum() const { return (_mode); };

    //!
    //! Set the current wavelet
    //!
    //! Change the current wavelet to the one specified by \p wname.
    //! \param[in] wname Name of wavelet.
    //!
    //! \retval status a non-negative int is returned on success
    //!
    int wavelet(const string &wname);

    //! Get the current discrete wavelet name
    //!
    //! \retval name
    //!
    string wavelet_name() const { return (_wname); };

    //! Get the current discrete wavelet
    //!
    //! \retval wavelet
    //!
    const WaveFiltBase *wavelet() const { return (_wf); };

    //! Returns length of approximation coefficients generated in a
    //! decompostition pass
    //!
    //! This method returns the number of approximation coefficients
    //! generated by one decomposition pass through the filter bank for a signal
    //! of length, \p sigInLen.
    //!
    //! \param[in] sigInLen Length of input signal (number of samples)
    //! \retval length On success returns the number of coefficients. A
    //! negative int is returned on failure.
    //!
    //! \sa MatWaveDwt::dwt()
    //
    size_t approxlength(size_t sigInLen) const;

    //! Returns length of detail coefficients generated in a
    //! decompostition pass
    //!
    //! This method returns the number of detail coefficients
    //! generated by one decomposition pass through the filter bank for a signal
    //! of length, \p sigInLen.
    //!
    //! \param[in] sigInLen Length of input signal (number of samples)
    //! \retval length Returns the number of coefficients.
    //!
    //! \sa MatWaveDwt::dwt()
    //
    size_t detaillength(size_t sigInLen) const;

    //! Returns length of coefficients generated in a decompostition pass
    //!
    //! This method returns the number of coefficients (approximation plus detail)
    //! generated by one decomposition pass through the filter bank for a signal
    //! of length, \p sigInLen.
    //!
    //! \param[in] sigInLen Length of input signal (number of samples)
    //! \retval length Returns the number of coefficients.
    //!
    //! \sa MatWaveDwt::dwt()
    //
    size_t coefflength(size_t sigInLen) const {
        return (approxlength(sigInLen) + detaillength(sigInLen));
    };

    size_t coefflength2(size_t sigInX, size_t sigInY) const {
        return (coefflength(sigInX) * coefflength(sigInY));
    };

    size_t coefflength3(size_t sigInX, size_t sigInY, size_t sigInZ) const {
        return (coefflength(sigInX) * coefflength(sigInY) * coefflength(sigInZ));
    };

    //! Returns maximum wavelet decompostion level
    //!
    //! This method returns the maximum level decomposition of a signal
    //! of length, \p s. This is the
    //! maximum number of times that a single level decomposition can
    //! be applied to a signal
    //!
    //! \param[in] Length of input signal
    //! \retval length Returns the maximum number of
    //! decompositions.
    //!
    //! \sa MatWaveDwt::dwt(), MatWaveWavedec::wavedec()
    //
    size_t wmaxlev(size_t s) const;

    //! Set or get the abort-on-invalid-float flag
    //!
    //! When set, the presence of input data containing invalid floats - floats
    //! for which the math.h isfinite() function does not return true - results
    //! in the abnormal termination of the method. If the flag is not
    //! set invalid floats are set to zero. By default the flag is not set.
    //!
    //! \retval flag A reference to the abot-on-invalid-float flag
    //
    bool &InvalidFloatAbortOnOff() { return (_InvalidFloatAbort); };

  protected:
  private:
    bool _InvalidFloatAbort;
    dwtmode_t _mode;
    WaveFiltBase *_wf;
    string _wname;

    WaveFiltBase *_create_wf(const string &wname) const;

    void _wave_len_validate(size_t sigInLen, int waveLength, size_t *lev, size_t *val) const;

    dwtmode_t _dwtmodestr2enum(const string &mode) const;
    string _dwtmodeenum2str(dwtmode_t mode) const;
};

} // namespace VAPoR

#endif

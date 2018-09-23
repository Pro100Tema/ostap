// ============================================================================
#ifndef OSTAP_MODELS2D_H 
#define OSTAP_MODELS2D_H 1
// ============================================================================
// include files
// ============================================================================
// STD & STL
// ============================================================================
#include <vector>
#include <complex>
// ============================================================================
// Ostap
// ============================================================================
#include "Ostap/Models.h"
#include "Ostap/Bernstein2D.h"
// ============================================================================
/** @file Ostap/Models2D.h
 *  collection of 2D-models
 *  @author Vanya BELYAEV Ivan.Belyaev@itep.ru
 *  @date 2010-04-19
 */
// ============================================================================
namespace Ostap
{
  // ==========================================================================
  namespace Math
  {
    // ========================================================================
    /** @class PS2DPol
     *  The 2D-function, that represent a cross-product of two phase-space factors,
     *  \f$ Ps_x(x)\f$ and \f$ Ps_y(y)\f$,  modulated by the 2D-positive polynomial.
     *
     *  The function is:
     *  \f[ f(x,y) = Ps_{x}(x) Ps_{y}(y) P_{pos}(x,y)\f], where 
     *  - \f$ Ps_x(x)\f$ and \f$ Ps_y(y)\f$ are 1D phase-space functions 
     *  - \f$ P_{pos}(x,y) \f$ is 2D positive Bernstein polynomial 
     *  @see Ostap::Math::PhaseSpaceNL 
     *  @see Ostap::Math::Positive2D
     */
    class  PS2DPol
    {
      // ======================================================================
    public:
      // ======================================================================
      /// constructor from the order
      PS2DPol ( const PhaseSpaceNL&   psx  = PhaseSpaceNL () ,
                const PhaseSpaceNL&   psy  = PhaseSpaceNL () ,
                const unsigned short  Nx   =   1 ,
                const unsigned short  Ny   =   1 ) ;
      /// constructor from the order
      PS2DPol ( const PhaseSpaceNL&   psx        ,
                const PhaseSpaceNL&   psy        ,
                const unsigned short  Nx         ,
                const unsigned short  Ny         ,
                const double          xmin       ,
                const double          xmax       ,
                const double          ymin       ,
                const double          ymax       ) ;
      // ======================================================================
    public:
      // ======================================================================
      /// get the value
      double operator () ( const double x , const double y ) const ;
      // ======================================================================
    public:
      // ======================================================================
      /// get number of parameters
      std::size_t npars () const { return m_positive.npars () ; }
      /// set k-parameter
      bool setPar       ( const unsigned int k , const double value )
      { return m_positive.setPar ( k , value ) ;}
      /// set k-parameter
      bool setParameter ( const unsigned int k , const double value )
      { return setPar   ( k , value ) ; }
      /// get the parameter value
      double  par       ( const unsigned int k ) const
      { return m_positive.par ( k ) ; }
      /// get the parameter value
      double  parameter ( const unsigned int k ) const { return par ( k ) ; }
      /// get parameters/phases 
      const std::vector<double>& pars() const { return m_positive.pars() ; }
      /// get nX & nY
      unsigned short nX () const { return m_positive.nX () ; }
      unsigned short nY () const { return m_positive.nY () ; }
      // ======================================================================
    public:
      // ======================================================================
      double xmin () const { return m_positive.xmin () ; }
      double xmax () const { return m_positive.xmax () ; }
      double ymin () const { return m_positive.ymin () ; }
      double ymax () const { return m_positive.ymax () ; }
      // ======================================================================
    public:
      // ======================================================================
      /** get the integral over 2D-region
       *  \f[ \int_{x_low}^{x_high}\int_{y_low}^{y_high} \mathcal{B}(x,y) \mathrm{d}x\mathrm{d}y\f]
       *  @param xlow  low  edge in x
       *  @param xhigh high edge in x
       *  @param ylow  low  edge in y
       *  @param yhigh high edge in y
       */
      double integral ( const double xlow  ,
                        const double xhigh ,
                        const double ylow  , 
                        const double yhigh ) const ;
      /** integral over x-dimension
       *  \f[ \int_{y_low}^{y_high} \mathcal{B}(x,y) \mathrm{d}y\f]
       *  @param y     variable
       *  @param xlow  low  edge in y
       *  @param xhigh high edge in y
       */
      double integrateX ( const double y     ,
                          const double xlow  , 
                          const double xhigh ) const ;
      /** integral over x-dimension
       *  \f[ \int_{x_low}^{x_high} \mathcal{B}(x,y) \mathrm{d}x\f]
       *  @param x     variable
       *  @param ylow  low  edge in x
       *  @param yhigh high edge in x
       */
      double integrateY ( const double x     ,
                          const double ylow  ,
                          const double yhigh ) const ;
      // ======================================================================
    public:
      // ======================================================================
      const Ostap::Math::PhaseSpaceNL& psX         () const { return m_psx      ; }
      const Ostap::Math::PhaseSpaceNL& psY         () const { return m_psy      ; }
      const Ostap::Math::PhaseSpaceNL& phasespaceX () const { return psX ()     ; }
      const Ostap::Math::PhaseSpaceNL& phasespaceY () const { return psY ()     ; }
      const Ostap::Math::Positive2D&   positive    () const { return m_positive ; }
      const Ostap::Math::Positive2D&   polynom     () const { return m_positive ; }
      // ====================================== ===============================
    private: // helper function to make the calculations
      // ======================================================================
      /// helper function to make calculations
      double calculate ( const std::vector<double>& fx , 
                         const std::vector<double>& fy ) const ;
      // ======================================================================
    private:
      // ======================================================================
      /// the actual (positive) bernstein polynomial in 2D
      Ostap::Math::Positive2D   m_positive ; // the actual bernstein polynomial
      /// Phase space
      Ostap::Math::PhaseSpaceNL m_psx      ;
      Ostap::Math::PhaseSpaceNL m_psy      ;
      // ======================================================================
    private:
      // ======================================================================
      /// workspace
      Ostap::Math::WorkSpace m_workspace   ;
      // ======================================================================
    };
    // ========================================================================
    /** @class PS2DPolSym
     *  The symmetric 2D-function, that represent a cross-product 
     *  of two identical phase-space factors,
     *  \f$ Ps(x)\f$ and \f$ Ps(y)\f$,  modulated by the symmetric 2D-positive 
     *  polynomial.
     * 
     *  The function is:
     *  \f[ f(x,y) = Ps(x) Ps(y) P_{pos}(x,y) \f], where 
     *  - \f$ Ps_x(x)\f$ and \f$ Ps_y(y)\f$ are 1D phase-space functions 
     *  - \f$ P_{pos}(x,y) \f$ is symmetric 2D positive Bernstein polynomial 
     *
     * Clearly the function is symmetric under 
     * \f$ x\leftrightarrow y \f$ transformation: \f$f(x,y) = f(y,x) \f$ 
     *  @see Ostap::Math::PhaseSpaceNL 
     *  @see Ostap::Math::Positive2DSym
     */
    class  PS2DPolSym
    {
      // ======================================================================
    public:
      // ======================================================================
      /// constructor from the order
      PS2DPolSym ( const PhaseSpaceNL&   ps   = PhaseSpaceNL() ,
                   const unsigned short  N    =  1             ) ;
      /// constructor from the order
      PS2DPolSym ( const PhaseSpaceNL&   ps         ,
                   const unsigned short  N          ,
                   const double          xmin       ,
                   const double          xmax       ) ;
      // ======================================================================
    public:
      // ======================================================================
      /// get the value
      double operator () ( const double x , const double y ) const ;
      // ======================================================================
    public:
      // ======================================================================
      /// get number of parameters
      std::size_t npars () const { return m_positive.npars () ; }
      /// set k-parameter
      bool setPar       ( const unsigned int k , const double value )
      { return m_positive.setPar ( k , value ) ;}
      /// set k-parameter
      bool setParameter ( const unsigned int k , const double value )
      { return setPar   ( k , value ) ; }
      /// get the parameter value
      double  par       ( const unsigned int k ) const
      { return m_positive.par ( k ) ; }
      /// get the parameter value
      double  parameter ( const unsigned int k ) const { return par ( k ) ; }
      /// get parameters/phases 
      const std::vector<double>& pars() const { return m_positive.pars() ; }
      /// get nX & nY
      unsigned short nX () const { return m_positive.nX () ; }
      unsigned short nY () const { return m_positive.nY () ; }
      // ======================================================================
    public:
      // ======================================================================
      double xmin () const { return m_positive.xmin () ; }
      double xmax () const { return m_positive.xmax () ; }
      double ymin () const { return m_positive.ymin () ; }
      double ymax () const { return m_positive.ymax () ; }
      // ======================================================================
    public:
      // ======================================================================
      /** get the integral over 2D-region
       *  \f[ \int_{x_low}^{x_high}\int_{y_low}^{y_high} \mathcal{B}(x,y) \mathrm{d}x\mathrm{d}y\f]
       *  @param xlow  low  edge in x
       *  @param xhigh high edge in x
       *  @param ylow  low  edge in y
       *  @param yhigh high edge in y
       */
      double integral ( const double xlow  , 
                        const double xhigh ,
                        const double ylow  , 
                        const double yhigh ) const ;
      /** integral over x-dimension
       *  \f[ \int_{y_low}^{y_high} \mathcal{B}(x,y) \mathrm{d}y\f]
       *  @param y     variable
       *  @param xlow  low  edge in y
       *  @param xhigh high edge in y
       */
      double integrateX ( const double y     ,
                          const double xlow  , 
                          const double xhigh ) const ;
      /** integral over x-dimension
       *  \f[ \int_{x_low}^{x_high} \mathcal{B}(x,y) \mathrm{d}x\f]
       *  @param x     variable
       *  @param ylow  low  edge in x
       *  @param yhigh high edge in x
       */
      double integrateY ( const double x     ,
                          const double ylow  ,
                          const double yhigh ) const ;
      // ======================================================================
    public:
      // ======================================================================
      const Ostap::Math::PhaseSpaceNL&  psX         () const { return m_ps       ; }
      const Ostap::Math::PhaseSpaceNL&  psY         () const { return m_ps       ; }
      const Ostap::Math::PhaseSpaceNL&  phasespaceX () const { return psX()      ; }
      const Ostap::Math::PhaseSpaceNL&  phasespaceY () const { return psY()      ; }
      const Ostap::Math::Positive2DSym& positive    () const { return m_positive ; }
      const Ostap::Math::Positive2DSym& polynom     () const { return m_positive ; }
      // ====================================== ===============================
    private: // helper functions to make the calculations
      // ======================================================================
      /// helper function to make calculations
      double calculate ( const std::vector<double>& fx , 
                         const std::vector<double>& fy ) const ;
      // ======================================================================
    private:
      // ======================================================================
      /// the actual (positive) bernstein polynomial in 2D
      Ostap::Math::Positive2DSym m_positive ; // the actual bernstein polynomial
      /// Phase space
      Ostap::Math::PhaseSpaceNL m_ps        ;
      // ======================================================================
    private:
      // ======================================================================
      /// workspace for numerical integration
      Ostap::Math::WorkSpace m_workspace    ;
      // ======================================================================
    };
    // ========================================================================
    /** @class PS2DPol2
     *  The 2D-function, that represent a cross-product of two phase-space factors,
     *  \f$ Ps_x(x)\f$ and \f$ Ps_y(y)\f$,  modulated by the 2D-positive polynomial.
     *
     *  The function is:
     *  \f[ f(x,y) = Ps_{x}(x) Ps_{y}(y) P_{pos}(x,y)\f], where 
     *  - \f$ Ps_x(x)\f$ and \f$ Ps_y(y)\f$ are 1D phase-space functions 
     *  - \f$ P_{pos}(x,y) \f$ is 2D positive Bernstein polynomial 
     *  @see Ostap::Math::PhaseSpaceNL 
     *  @see Ostap::Math::Positive2D
     */
    class  PS2DPol2
    {
      // ======================================================================
    public:
      // ======================================================================
      /// constructor from the order
      PS2DPol2 ( const PhaseSpaceNL&   psx  = PhaseSpaceNL () ,
                 const PhaseSpaceNL&   psy  = PhaseSpaceNL () ,
                 const double          mmax =  -1 ,  
                 const unsigned short  Nx   =   1 ,
                 const unsigned short  Ny   =   1 ) ;
      /// constructor from the order
      PS2DPol2 ( const PhaseSpaceNL&   psx        ,
                 const PhaseSpaceNL&   psy        ,
                 const double          mmax       ,  
                 const unsigned short  Nx         ,
                 const unsigned short  Ny         ,
                 const double          xmin       ,
                 const double          xmax       ,
                 const double          ymin       ,
                 const double          ymax       ) ;
      // ======================================================================
    public:
      // ======================================================================
      /// get the value
      double operator () ( const double x , const double y ) const ;
      // ======================================================================
    public:
      // ======================================================================
      /// get number of parameters
      std::size_t npars () const { return m_positive.npars () ; }
      /// set k-parameter
      bool setPar       ( const unsigned int k , const double value )
      { return m_positive.setPar ( k , value ) ;}
      /// set k-parameter
      bool setParameter ( const unsigned int k , const double value )
      { return setPar   ( k , value ) ; }
      /// get the parameter value
      double  par       ( const unsigned int k ) const
      { return m_positive.par ( k ) ; }
      /// get the parameter value
      double  parameter ( const unsigned int k ) const { return par ( k ) ; }
      /// get parameters/phases 
      const std::vector<double>& pars() const { return m_positive.pars() ; }
      /// get nX & nY
      unsigned short nX () const { return m_positive.nX () ; }
      unsigned short nY () const { return m_positive.nY () ; }
      // ======================================================================
    public:
      // ======================================================================
      double xmin () const { return m_positive.xmin () ; }
      double xmax () const { return m_positive.xmax () ; }
      double ymin () const { return m_positive.ymin () ; }
      double ymax () const { return m_positive.ymax () ; }
      double mmax () const { return m_mmax             ; }
      // ======================================================================
    public:
      // ======================================================================
      /** get the integral over 2D-region
       *  \f[ \int_{x_low}^{x_high}\int_{y_low}^{y_high} \mathcal{B}(x,y) \mathrm{d}x\mathrm{d}y\f]
       *  @param xlow  low  edge in x
       *  @param xhigh high edge in x
       *  @param ylow  low  edge in y
       *  @param yhigh high edge in y
       */
      double integral ( const double xlow  ,
                        const double xhigh ,
                        const double ylow  , 
                        const double yhigh ) const ;
      /** integral over x-dimension
       *  \f[ \int_{y_low}^{y_high} \mathcal{B}(x,y) \mathrm{d}y\f]
       *  @param y     variable
       *  @param xlow  low  edge in y
       *  @param xhigh high edge in y
       */
      double integrateX ( const double y     ,
                          const double xlow  , 
                          const double xhigh ) const ;
      /** integral over x-dimension
       *  \f[ \int_{x_low}^{x_high} \mathcal{B}(x,y) \mathrm{d}x\f]
       *  @param x     variable
       *  @param ylow  low  edge in x
       *  @param yhigh high edge in x
       */
      double integrateY ( const double x     ,
                          const double ylow  ,
                          const double yhigh ) const ;
      // ======================================================================
    public:
      // ======================================================================
      const Ostap::Math::PhaseSpaceNL& psX         () const { return m_psx      ; }
      const Ostap::Math::PhaseSpaceNL& psY         () const { return m_psy      ; }
      const Ostap::Math::PhaseSpaceNL& phasespaceX () const { return psX ()     ; }
      const Ostap::Math::PhaseSpaceNL& phasespaceY () const { return psY ()     ; }
      const Ostap::Math::Positive2D&   positive    () const { return m_positive ; }
      const Ostap::Math::Positive2D&   polynom     () const { return m_positive ; }
      // ====================================== ===============================
    private:
      // ======================================================================
      /// the actual (positive) bernstein polynomial in 2D
      Ostap::Math::Positive2D   m_positive ; // the actual bernstein polynomial
      /// Phase space
      Ostap::Math::PhaseSpaceNL m_psx      ;
      Ostap::Math::PhaseSpaceNL m_psy      ;
      /// Max-mass 
      double                    m_mmax     ;
      // ======================================================================
    private:
      // ======================================================================
      /// Phase space
      mutable Ostap::Math::PhaseSpaceNL m_psx_aux ;
      mutable Ostap::Math::PhaseSpaceNL m_psy_aux ;
      // ======================================================================
      /// workspace
      Ostap::Math::WorkSpace m_workspace   ;
      // ======================================================================
    };
    // ========================================================================
    /** @class PS2DPol2Sym
     *  The symmetric 2D-function, that represent a cross-product 
     *  of two identical phase-space factors,
     *  \f$ Ps(x)\f$ and \f$ Ps(y)\f$,  modulated by the symmetric 2D-positive 
     *  polynomial.
     * 
     *  The function is:
     *  \f[ f(x,y) = Ps(x) Ps(y) P_{pos}(x,y) \f], where 
     *  - \f$ Ps_x(x)\f$ and \f$ Ps_y(y)\f$ are 1D phase-space functions 
     *  - \f$ P_{pos}(x,y) \f$ is symmetric 2D positive Bernstein polynomial 
     *
     * Clearly the function is symmetric under 
     * \f$ x\leftrightarrow y \f$ transformation: \f$f(x,y) = f(y,x) \f$ 
     *  @see Ostap::Math::PhaseSpaceNL 
     *  @see Ostap::Math::Positive2DSym
     */
    class  PS2DPol2Sym
    {
      // ======================================================================
    public:
      // ======================================================================
      /// constructor from the order
      PS2DPol2Sym ( const PhaseSpaceNL&   ps   = PhaseSpaceNL() ,
                    const double          mmax =  -1            ,  
                    const unsigned short  N    =   1            ) ;
      /// constructor from the order
      PS2DPol2Sym ( const PhaseSpaceNL&   ps         ,
                    const double          mmax       ,  
                    const unsigned short  N          ,
                    const double          xmin       ,
                    const double          xmax       ) ;
      // ======================================================================
    public:
      // ======================================================================
      /// get the value
      double operator () ( const double x , const double y ) const ;
      // ======================================================================
    public:
      // ======================================================================
      /// get number of parameters
      std::size_t npars () const { return m_positive.npars () ; }
      /// set k-parameter
      bool setPar       ( const unsigned int k , const double value )
      { return m_positive.setPar ( k , value ) ;}
      /// set k-parameter
      bool setParameter ( const unsigned int k , const double value )
      { return setPar   ( k , value ) ; }
      /// get the parameter value
      double  par       ( const unsigned int k ) const
      { return m_positive.par ( k ) ; }
      /// get the parameter value
      double  parameter ( const unsigned int k ) const { return par ( k ) ; }
      /// get parameters/phases 
      const std::vector<double>& pars() const { return m_positive.pars() ; }
      /// get nX & nY
      unsigned short nX () const { return m_positive.nX () ; }
      unsigned short nY () const { return m_positive.nY () ; }
      // ======================================================================
    public:
      // ======================================================================
      double xmin () const { return m_positive.xmin () ; }
      double xmax () const { return m_positive.xmax () ; }
      double ymin () const { return m_positive.ymin () ; }
      double ymax () const { return m_positive.ymax () ; }
      double mmax () const { return m_mmax             ; }
      // ======================================================================
    public:
      // ======================================================================
      /** get the integral over 2D-region
       *  \f[ \int_{x_low}^{x_high}\int_{y_low}^{y_high} \mathcal{B}(x,y) \mathrm{d}x\mathrm{d}y\f]
       *  @param xlow  low  edge in x
       *  @param xhigh high edge in x
       *  @param ylow  low  edge in y
       *  @param yhigh high edge in y
       */
      double integral ( const double xlow  , 
                        const double xhigh ,
                        const double ylow  , 
                        const double yhigh ) const ;
      /** integral over x-dimension
       *  \f[ \int_{y_low}^{y_high} \mathcal{B}(x,y) \mathrm{d}y\f]
       *  @param y     variable
       *  @param xlow  low  edge in y
       *  @param xhigh high edge in y
       */
      double integrateX ( const double y     ,
                          const double xlow  , 
                          const double xhigh ) const ;
      /** integral over x-dimension
       *  \f[ \int_{x_low}^{x_high} \mathcal{B}(x,y) \mathrm{d}x\f]
       *  @param x     variable
       *  @param ylow  low  edge in x
       *  @param yhigh high edge in x
       */
      double integrateY ( const double x     ,
                          const double ylow  ,
                          const double yhigh ) const ;
      // ======================================================================
    public:
      // ======================================================================
      const Ostap::Math::PhaseSpaceNL&  psX         () const { return m_ps       ; }
      const Ostap::Math::PhaseSpaceNL&  psY         () const { return m_ps       ; }
      const Ostap::Math::PhaseSpaceNL&  phasespaceX () const { return psX()      ; }
      const Ostap::Math::PhaseSpaceNL&  phasespaceY () const { return psY()      ; }
      const Ostap::Math::Positive2DSym& positive    () const { return m_positive ; }
      const Ostap::Math::Positive2DSym& polynom     () const { return m_positive ; }
      // ====================================== ===============================
    private:
      // ======================================================================
      /// the actual (positive) bernstein polynomial in 2D
      Ostap::Math::Positive2DSym m_positive ; // the actual bernstein polynomial
      /// Phase space
      Ostap::Math::PhaseSpaceNL m_ps        ;
      // ======================================================================
      /// Max-mass 
      double                    m_mmax           ;
      // ======================================================================
    private:
      // ======================================================================
      /// Phase space
      mutable Ostap::Math::PhaseSpaceNL m_psx_aux ;
      mutable Ostap::Math::PhaseSpaceNL m_psy_aux ;
      // ======================================================================
    private:
      // ======================================================================
      /// workspace for numerical integration
      Ostap::Math::WorkSpace m_workspace    ;
      // ======================================================================
    };
    // ========================================================================
    /** @class PS2DPol3
     *  The 2D-function, that represent a cross-product of two phase-space factors,
     *  \f$ Ps_x(x)\f$ and \f$ Ps_y(y)\f$,  modulated by the 2D-positive polynomial.
     *
     *  The function is:
     *  \f[ f(x,y) = Ps_{x}(x) Ps_{y}(y) P_{pos}(x,y)\f], where 
     *  - \f$ Ps_x(x)\f$ and \f$ Ps_y(y)\f$ are 1D phase-space functions 
     *  - \f$ P_{pos}(x,y) \f$ is 2D positive Bernstein polynomial 
     *  @see Ostap::Math::PhaseSpaceNL 
     *  @see Ostap::Math::Positive2D
     */
    class  PS2DPol3
    {
      // ======================================================================
    public:
      // ======================================================================
      /// constructor from the order
      PS2DPol3 ( const PhaseSpaceNL&   psx  = PhaseSpaceNL () ,
                 const PhaseSpaceNL&   psy  = PhaseSpaceNL () ,
                 const double          mmax =  -1 ,  
                 const unsigned short  Nx   =   1 ,
                 const unsigned short  Ny   =   1 ) ;
      /// constructor from the order
      PS2DPol3 ( const PhaseSpacePol&  psx        ,
                 const PhaseSpacePol&  psy        ,
                 const double          mmax =  -1 ) ;
      /// constructor from the order
      PS2DPol3 ( const PhaseSpaceNL&   psx        ,
                 const PhaseSpaceNL&   psy        ,
                 const double          mmax       ,  
                 const unsigned short  Nx         ,
                 const unsigned short  Ny         ,
                 const double          xmin       ,
                 const double          xmax       ,
                 const double          ymin       ,
                 const double          ymax       ) ;
      // ======================================================================
    public:
      // ======================================================================
      /// get the value
      double operator () ( const double x , const double y ) const ;
      // ======================================================================
    public:
      // ======================================================================
      /// get number of parameters
      std::size_t npars () const { return m_psx.npars () + m_psy.npars() ; }
      /// set k-parameter
      bool setPar       ( const unsigned int k , const double value )
      { 
        const unsigned int npx = m_psx.npars() ;
        return 
          k < npx     ? 
          m_psx.setPar ( k       , value ) :
          m_psy.setPar ( k - npx , value ) ;
      }
      /// set k-parameter
      bool setParameter ( const unsigned int k , const double value )
      { return setPar   ( k , value ) ; }
      /// get the parameter value
      double  par       ( const unsigned int k ) const
      {
        const unsigned int npx = m_psx.npars() ;
        return 
          k < npx     ? 
          m_psx.par ( k       ) :
          m_psy.par ( k - npx ) ;
      }
      /// get the parameter value
      double  parameter ( const unsigned int k ) const { return par ( k ) ; }
      /// get parameters/phases 
      std::vector<double> pars() const ;
      /// x-parameters 
      const std::vector<double>& xpars() const { return m_psx.pars() ; }
      /// y-parameters 
      const std::vector<double>& ypars() const { return m_psy.pars() ; }      
      /// get nX & nY
      unsigned short nX () const { return m_psx.n () ; }
      unsigned short nY () const { return m_psy.n () ; }
      // ======================================================================
    public:
      // ======================================================================
      double xmin () const { return m_psx.xmin () ; }
      double xmax () const { return m_psx.xmax () ; }
      double ymin () const { return m_psy.xmin () ; }
      double ymax () const { return m_psy.xmax () ; }
      double mmax () const { return m_mmax        ; }
      // ======================================================================
    public:
      // ======================================================================
      /** get the integral over 2D-region
       *  \f[ \int_{x_low}^{x_high}\int_{y_low}^{y_high} \mathcal{B}(x,y) \mathrm{d}x\mathrm{d}y\f]
       *  @param xlow  low  edge in x
       *  @param xhigh high edge in x
       *  @param ylow  low  edge in y
       *  @param yhigh high edge in y
       */
      double integral ( const double xlow  ,
                        const double xhigh ,
                        const double ylow  , 
                        const double yhigh ) const ;
      /** integral over x-dimension
       *  \f[ \int_{y_low}^{y_high} \mathcal{B}(x,y) \mathrm{d}y\f]
       *  @param y     variable
       *  @param xlow  low  edge in y
       *  @param xhigh high edge in y
       */
      double integrateX ( const double y     ,
                          const double xlow  , 
                          const double xhigh ) const ;
      /** integral over x-dimension
       *  \f[ \int_{x_low}^{x_high} \mathcal{B}(x,y) \mathrm{d}x\f]
       *  @param x     variable
       *  @param ylow  low  edge in x
       *  @param yhigh high edge in x
       */
      double integrateY ( const double x     ,
                          const double ylow  ,
                          const double yhigh ) const ;
      // ======================================================================
    public:
      // ======================================================================
      const Ostap::Math::PhaseSpacePol& psX         () const { return m_psx  ; }
      const Ostap::Math::PhaseSpacePol& psY         () const { return m_psy  ; }
      const Ostap::Math::PhaseSpacePol& phasespaceX () const { return psX () ; }
      const Ostap::Math::PhaseSpacePol& phasespaceY () const { return psY () ; }
      // ====================================== ===============================
    private:
      // ======================================================================
      /// Phase space
      Ostap::Math::PhaseSpacePol m_psx      ;
      Ostap::Math::PhaseSpacePol m_psy      ;
      /// Max-mass 
      double                    m_mmax     ;
      // ======================================================================
    private:
      // ======================================================================
      /// Phase space
      mutable Ostap::Math::PhaseSpaceNL m_psx_aux ;
      mutable Ostap::Math::PhaseSpaceNL m_psy_aux ;
      // ======================================================================
      /// workspace
      Ostap::Math::WorkSpace m_workspace   ;
      // ======================================================================
    };
    // ========================================================================
    /** @class PS2DPol3Sym
     *  The 2D-function, that represent a cross-product of two phase-space factors,
     *  \f$ Ps_x(x)\f$ and \f$ Ps_y(y)\f$,  modulated by the 2D-positive polynomial.
     *
     *  The function is:
     *  \f[ f(x,y) = Ps_{x}(x) Ps_{y}(y) P_{pos}(x,y)\f], where 
     *  - \f$ Ps_x(x)\f$ and \f$ Ps_y(y)\f$ are 1D phase-space functions 
     *  - \f$ P_{pos}(x,y) \f$ is 2D positive Bernstein polynomial 
     *  @see Ostap::Math::PhaseSpaceNL 
     *  @see Ostap::Math::Positive2D
     */
    class  PS2DPol3Sym
    {
      // ======================================================================
    public:
      // ======================================================================
      /// constructor from the order
      PS2DPol3Sym ( const PhaseSpaceNL&   ps   = PhaseSpaceNL () ,
                    const double          mmax =  -1 ,  
                    const unsigned short  N    =   1 ) ;
      /// constructor from the order
      PS2DPol3Sym ( const PhaseSpacePol&  ps         ,
                    const double          mmax =  -1 ) ;
      /// constructor from the order
      PS2DPol3Sym ( const PhaseSpaceNL&   ps         ,
                    const double          mmax       ,  
                    const unsigned short  N          ,
                    const double          xmin       ,
                    const double          xmax       );
      // ======================================================================
    public:
      // ======================================================================
      /// get the value
      double operator () ( const double x , const double y ) const ;
      // ======================================================================
    public:
      // ======================================================================
      /// get number of parameters
      std::size_t npars () const { return m_ps.npars ()  ; }
      /// set k-parameter
      bool setPar       ( const unsigned int k , const double value )
      { 
        const unsigned int np = m_ps.npars() ;
        return k < np ? m_ps.setPar ( k , value ) : m_ps.setPar ( k - np , value ) ;
      }
      /// set k-parameter
      bool setParameter ( const unsigned int k , const double value )
      { return setPar   ( k , value ) ; }
      /// get the parameter value
      double  par       ( const unsigned int k ) const
      {
        const unsigned int np = m_ps.npars() ;
        return k < np ? m_ps.par ( k  ) : m_ps.par ( k - np ) ;
      }
      /// get the parameter value
      double  parameter ( const unsigned int k ) const { return par ( k ) ; }
      /// get parameters/phases 
      const std::vector<double>& pars () const { return m_ps.pars() ; }
      /// get nX & nY
      unsigned short n  () const { return m_ps.n () ; }
      unsigned short nX () const { return m_ps.n () ; }
      unsigned short nY () const { return m_ps.n () ; }
      // ======================================================================
    public:
      // ======================================================================
      double xmin () const { return m_ps.xmin () ; }
      double xmax () const { return m_ps.xmax () ; }
      double ymin () const { return m_ps.xmin () ; }
      double ymax () const { return m_ps.xmax () ; }
      double mmax () const { return m_mmax       ; }
      // ======================================================================
    public:
      // ======================================================================
      /** get the integral over 2D-region
       *  \f[ \int_{x_low}^{x_high}\int_{y_low}^{y_high} \mathcal{B}(x,y) \mathrm{d}x\mathrm{d}y\f]
       *  @param xlow  low  edge in x
       *  @param xhigh high edge in x
       *  @param ylow  low  edge in y
       *  @param yhigh high edge in y
       */
      double integral ( const double xlow  ,
                        const double xhigh ,
                        const double ylow  , 
                        const double yhigh ) const ;
      /** integral over x-dimension
       *  \f[ \int_{y_low}^{y_high} \mathcal{B}(x,y) \mathrm{d}y\f]
       *  @param y     variable
       *  @param xlow  low  edge in y
       *  @param xhigh high edge in y
       */
      double integrateX ( const double y     ,
                          const double xlow  , 
                          const double xhigh ) const ;
      /** integral over x-dimension
       *  \f[ \int_{x_low}^{x_high} \mathcal{B}(x,y) \mathrm{d}x\f]
       *  @param x     variable
       *  @param ylow  low  edge in x
       *  @param yhigh high edge in x
       */
      double integrateY ( const double x     ,
                          const double ylow  ,
                          const double yhigh ) const ;
      // ======================================================================
    public:
      // ======================================================================
      const Ostap::Math::PhaseSpacePol& ps          () const { return m_ps   ; }
      const Ostap::Math::PhaseSpacePol& psX         () const { return m_ps   ; }
      const Ostap::Math::PhaseSpacePol& psY         () const { return m_ps   ; }
      const Ostap::Math::PhaseSpacePol& phasespace  () const { return ps  () ; }
      const Ostap::Math::PhaseSpacePol& phasespaceX () const { return psX () ; }
      const Ostap::Math::PhaseSpacePol& phasespaceY () const { return psY () ; }
      // ====================================== ===============================
    private:
      // ======================================================================
      /// Phase space
      Ostap::Math::PhaseSpacePol m_ps  ;
      /// Max-mass 
      double                    m_mmax ;
      // ======================================================================
    private:
      // ======================================================================
      /// Phase space
      mutable Ostap::Math::PhaseSpaceNL m_psx_aux ;
      mutable Ostap::Math::PhaseSpaceNL m_psy_aux ;
      // ======================================================================
      /// workspace
      Ostap::Math::WorkSpace m_workspace   ;
      // ======================================================================
    };
    // ========================================================================
    /** @class ExpoPS2DPol
     *  The 2D-function:
     *  \f$ f(x,y) = exp(tau*x)*Ps(y)*P_{pos}(x,y) \f$, where
     *  \f$Ps\f$ denotes phase-space function and
     * \f$P_{pos}\f$ denotes the positive polynomial
     */
    class  ExpoPS2DPol
    {
      // ======================================================================
    public:
      // ======================================================================
      /// constructor from the order
      ExpoPS2DPol ( const PhaseSpaceNL&   psy  = PhaseSpaceNL() ,
                    const double          xmin = 0 ,
                    const double          xmax = 1 ,
                    const unsigned short  Nx   = 1 ,
                    const unsigned short  Ny   = 1 ,
                    const double          tau  = 0 ) ;
      /// constructor from the order
      ExpoPS2DPol ( const PhaseSpaceNL&   psy      ,
                    const double          xmin     ,
                    const double          xmax     ,
                    const unsigned short  Nx       ,
                    const unsigned short  Ny       ,
                    const double          ymin     ,
                    const double          ymax     ,
                    const double          tau  = 0 ) ;
      // ======================================================================
    public:
      // ======================================================================
      /// get the value
      double operator () ( const double x , const double y ) const ;
      // ======================================================================
    public:
      // ======================================================================
      /// get number of parameters
      std::size_t npars () const { return m_positive.npars () ; }
      /// set k-parameter
      bool setPar       ( const unsigned int k , const double value )
      { return m_positive.setPar ( k , value ) ;}
      /// set k-parameter
      bool setParameter ( const unsigned int k , const double value )
      { return setPar   ( k , value ) ; }
      /// get the parameter value
      double  par       ( const unsigned int k ) const
      { return m_positive.par ( k ) ; }
      /// get the parameter value
      double  parameter ( const unsigned int k ) const { return par ( k ) ; }
      /// get nX & nY
      unsigned short nX () const { return m_positive.nX () ; }
      unsigned short nY () const { return m_positive.nY () ; }
      // ======================================================================
    public:
      // ======================================================================
      double xmin () const { return m_positive.xmin () ; }
      double xmax () const { return m_positive.xmax () ; }
      double ymin () const { return m_positive.ymin () ; }
      double ymax () const { return m_positive.ymax () ; }
      // ======================================================================
    public:
      // ======================================================================
      /// get tau
      double         tau () const { return m_tau ;}
      /// set tau
      bool           setTau ( const double val ) ;
      // ======================================================================
    public:
      // ======================================================================
      /** get the integral over 2D-region
       *  \f[ \int_{x_low}^{x_high}\int_{y_low}^{y_high} \mathcal{B}(x,y) \mathrm{d}x\mathrm{d}y\f]
       *  @param xlow  low  edge in x
       *  @param xhigh high edge in x
       *  @param ylow  low  edge in y
       *  @param yhigh high edge in y
       */
      double integral ( const double xlow  ,
                        const double xhigh ,
                        const double ylow  , 
                        const double yhigh ) const ;
      /** integral over x-dimension
       *  \f[ \int_{y_low}^{y_high} \mathcal{B}(x,y) \mathrm{d}y\f]
       *  @param y     variable
       *  @param xlow  low  edge in y
       *  @param xhigh high edge in y
       */
      double integrateX ( const double y     ,
                          const double xlow  ,
                          const double xhigh ) const ;
      /** integral over x-dimension
       *  \f[ \int_{x_low}^{x_high} \mathcal{B}(x,y) \mathrm{d}x\f]
       *  @param x     variable
       *  @param ylow  low  edge in x
       *  @param yhigh high edge in x
       */
      double integrateY ( const double x     ,
                          const double ylow  ,
                          const double yhigh ) const ;
      // ======================================================================
    public:
      // ======================================================================
      const Ostap::Math::PhaseSpaceNL& psY         () const { return m_psy      ; }
      const Ostap::Math::PhaseSpaceNL& phasespaceY () const { return psY ()     ; }
      const Ostap::Math::Positive2D&   positive    () const { return m_positive ; }
      const Ostap::Math::Positive2D&   polynom     () const { return m_positive ; }
      // ====================================== ===============================
    private: // helper function to make the calculations
      // ======================================================================
      /// helper function to make calculations
      double calculate ( const std::vector<double>& fx , 
                         const std::vector<double>& fy ) const ;
      // ======================================================================
    private:
      // ======================================================================
      /// the actual (positive) bernstein polynomial in 2D
      Ostap::Math::Positive2D   m_positive ; // the actual bernstein polynomial
      /// Phase space
      Ostap::Math::PhaseSpaceNL m_psy      ;
      /// exponential
      double                    m_tau      ;
      // ======================================================================
    private:
      // ======================================================================
      /// workspace
      Ostap::Math::WorkSpace m_workspace   ;
      // ======================================================================
    };
    // ========================================================================
    /** @class Expo2DPol
     *  The 2D-function:
     *  \f$ f(x,y) = exp(x)*expo(y)*P_{pos}(x,y) \f$, where
     * \f$P_{pos}\f$ denotes the positive polynomial
     */
    class  Expo2DPol
    {
      // ======================================================================
    public:
      // ======================================================================
      /// constructor from the order
      Expo2DPol ( const double          xmin = 0  ,
                  const double          xmax = 1  ,
                  const double          ymin = 0  ,
                  const double          ymax = 1  ,
                  const unsigned short  Nx   =  1 ,
                  const unsigned short  Ny   =  1 ,
                  const double          taux =  0 ,
                  const double          tauy =  0 ) ;            
      // ======================================================================
    public:
      // ======================================================================
      /// get the value
      double operator () ( const double x , const double y ) const ;
      // ======================================================================
    public:
      // ======================================================================
      /// get number of parameters
      std::size_t npars () const { return m_positive.npars () ; }
      /// set k-parameter
      bool setPar       ( const unsigned int k , const double value )
      { return m_positive.setPar ( k , value ) ;}
      /// set k-parameter
      bool setParameter ( const unsigned int k , const double value )
      { return setPar   ( k , value ) ; }
      /// get the parameter value
      double  par       ( const unsigned int k ) const
      { return m_positive.par ( k ) ; }
      /// get the parameter value
      double  parameter ( const unsigned int k ) const { return par ( k ) ; }
      /// get nX & nY
      unsigned short nX () const { return m_positive.nX () ; }
      unsigned short nY () const { return m_positive.nY () ; }
      // ======================================================================
    public:
      // ======================================================================
      double xmin () const { return m_positive.xmin () ; }
      double xmax () const { return m_positive.xmax () ; }
      double ymin () const { return m_positive.ymin () ; }
      double ymax () const { return m_positive.ymax () ; }
      // ======================================================================
    public:
      // ======================================================================
      /// get tau
      double         tauX    () const { return m_tauX ;}
      double         tauY    () const { return m_tauY ;}
      /// set tau
      bool           setTauX ( const double val ) ;
      bool           setTauY ( const double val ) ;
      // ======================================================================
    public:
      // ======================================================================
      /** get the integral over 2D-region
       *  \f[ \int_{x_low}^{x_high}\int_{y_low}^{y_high} \mathcal{B}(x,y) \mathrm{d}x\mathrm{d}y\f]
       *  @param xlow  low  edge in x
       *  @param xhigh high edge in x
       *  @param ylow  low  edge in y
       *  @param yhigh high edge in y
       */
      double integral ( const double xlow  ,
                        const double xhigh ,
                        const double ylow  , 
                        const double yhigh ) const ;
      /** integral over x-dimension
       *  \f[ \int_{y_low}^{y_high} \mathcal{B}(x,y) \mathrm{d}y\f]
       *  @param y     variable
       *  @param xlow  low  edge in y
       *  @param xhigh high edge in y
       */
      double integrateX ( const double y     ,
                          const double xlow  ,
                          const double xhigh ) const ;
      /** integral over x-dimension
       *  \f[ \int_{x_low}^{x_high} \mathcal{B}(x,y) \mathrm{d}x\f]
       *  @param x     variable
       *  @param ylow  low  edge in x
       *  @param yhigh high edge in x
       */
      double integrateY ( const double x     ,
                          const double ylow  , 
                          const double yhigh ) const ;
      // ======================================================================
    public:
      // ======================================================================
      const Ostap::Math::Positive2D&   positive    () const { return m_positive ; }
      const Ostap::Math::Positive2D&   polynom     () const { return m_positive ; }
      // ====================================== ===============================
    private: // helper function to make the calculations
      // ======================================================================
      /// helper function to make calculations
      double calculate ( const std::vector<double>& fx , 
                         const std::vector<double>& fy ) const ;
      // ======================================================================
    private:
      // ======================================================================
      /// the actual (positive) bernstein polynomial in 2D
      Ostap::Math::Positive2D   m_positive ; // the actual bernstein polynomial
      /// exponential
      double                    m_tauX     ;
      double                    m_tauY     ;
      // ======================================================================
    };
    // ========================================================================
    /** @class Expo2DPolSym
     *  The 2D-function:
     *  \f$ f(x,y) = exp(x)*expo(y)*P_{sym}(x,y) \f$, where
     * \f$P_{pos}\f$ denotes the symmetric positive polynomial
     */
    class  Expo2DPolSym
    {
      // ======================================================================
    public:
      // ======================================================================
      /// constructor from the order
      Expo2DPolSym ( const double          xmin = 0 ,
                     const double          xmax = 1 ,
                     const unsigned short  N    = 1 ,
                     const double          tau  = 0 ) ;
      // ======================================================================
    public:
      // ======================================================================
      /// get the value
      double operator () ( const double x , const double y ) const ;
      // ======================================================================
    public:
      // ======================================================================
      /// get number of parameters
      std::size_t npars () const { return m_positive.npars () ; }
      /// set k-parameter
      bool setPar       ( const unsigned int k , const double value )
      { return m_positive.setPar ( k , value ) ;}
      /// set k-parameter
      bool setParameter ( const unsigned int k , const double value )
      { return setPar   ( k , value ) ; }
      /// get the parameter value
      double  par       ( const unsigned int k ) const
      { return m_positive.par ( k ) ; }
      /// get the parameter value
      double  parameter ( const unsigned int k ) const { return par ( k ) ; }
      /// get nX & nY
      unsigned short n  () const { return m_positive.nX () ; }
      unsigned short nX () const { return m_positive.nX () ; }
      unsigned short nY () const { return m_positive.nY () ; }
      // ======================================================================
    public:
      // ======================================================================
      double xmin () const { return m_positive.xmin () ; }
      double xmax () const { return m_positive.xmax () ; }
      double ymin () const { return m_positive.ymin () ; }
      double ymax () const { return m_positive.ymax () ; }
      // ======================================================================
    public:
      // ======================================================================
      /// get tau
      double         tau     () const { return m_tau  ;}
      /// set tau
      bool           setTau  ( const double val ) ;
      // ======================================================================
    public:
      // ======================================================================
      /** get the integral over 2D-region
       *  \f[ \int_{x_low}^{x_high}\int_{y_low}^{y_high} \mathcal{B}(x,y) \mathrm{d}x\mathrm{d}y\f]
       *  @param xlow  low  edge in x
       *  @param xhigh high edge in x
       *  @param ylow  low  edge in y
       *  @param yhigh high edge in y
       */
      double integral ( const double xlow , const double xhigh ,
                        const double ylow , const double yhigh ) const ;
      /** integral over x-dimension
       *  \f[ \int_{y_low}^{y_high} \mathcal{B}(x,y) \mathrm{d}y\f]
       *  @param y     variable
       *  @param xlow  low  edge in y
       *  @param xhigh high edge in y
       */
      double integrateX ( const double y    ,
                          const double xlow , const double xhigh ) const ;
      /** integral over x-dimension
       *  \f[ \int_{x_low}^{x_high} \mathcal{B}(x,y) \mathrm{d}x\f]
       *  @param x     variable
       *  @param ylow  low  edge in x
       *  @param yhigh high edge in x
       */
      double integrateY ( const double x    ,
                          const double ylow , const double yhigh ) const ;
      // ======================================================================
    public:  // expose some internmals
      // ======================================================================
      const Ostap::Math::Positive2DSym& positive () const { return m_positive ; }
      const Ostap::Math::Positive2DSym& polynom  () const { return m_positive ; }
      // ====================================== ===============================
    private: // helper function to make the calculations
      // ======================================================================
      /// helper function to make calculations
      double calculate ( const std::vector<double>& fx , 
                         const std::vector<double>& fy ) const ;
      // ======================================================================
    private:
      // ======================================================================
      /// the actual (positive) bernstein polynomial in 2D
      Ostap::Math::Positive2DSym m_positive ; // the actual bernstein polynomial
      /// exponential
      double                     m_tau      ;
      // ======================================================================
    }; 
    // ========================================================================
  } //                                             end of namespace Ostap::Math
  // ==========================================================================
} //                                                     end of namespace Ostap
// ============================================================================
//                                                                      The END
// ============================================================================
#endif // OSTAP_MODELS2D_H
// ============================================================================

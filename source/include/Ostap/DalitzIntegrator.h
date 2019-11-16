// ===========================================================================
#ifndef OSTAP_DALITZINTEGRAL_H 
#define OSTAP_DALITZINTEGRAL_H 1
// ===========================================================================
namespace Ostap
{
  // =========================================================================
  namespace Math
  {
    // =======================================================================
    /** @class DalitzIntegrator DalitzIntegrtor.h Ostap/DalitzIntegrator.h
     *  Helper class to make the integration over Dalitz plane easy 
     *
     *  @author Vanya BELYAEV Ivan.Belyaev@itep.ru
     *  @date   2019-11-02
     */
    class DalitzIntegrator 
    {
    public: 
      // ======================================================================
      /// the actual type of 1D-function to integrate 
      typedef std::function<double(double)>               function1 ;
      /// the actual type of 2D-function to integrate 
      typedef std::function<double(double,double)>        function2 ;
      /// the actual type of 3D-function to integrate 
      typedef std::function<double(double,double,double)> function3 ;
      // ======================================================================
    public: 
      // ======================================================================
      /// Constructor
      DalitzIntegrator ( const double m1 , 
                         const double m2 , 
                         const double m3 ) ;
      // ======================================================================
    public : 
      // ======================================================================
      /** evaluate the integral over \f$s_1\f$ , \f$s_2\f$ variables 
       *  \f[ \int\int ds_1 ds_2 f(s, s_1,s_2) = 
       *  \int_{s_1^{min}}^{s_1^{max}} ds_1 
       *  \int_{s_2^{min}(s_1)}^{s_2^{max}(s_1)} ds_2 f(s,s_1,s_2)  \f] 
       *  @param M the overall mass of the system \f$\sqrt{s} \f$
       *  @param fs the function \f$ f(s, s_1,s_2)\f$ 
       *  @return the integral over dalitz plot
       */
      double integrate_s1s2 ( const double M , function3 f ) const ;
      // =======================================================================
      /** evaluate the integral over \f$s_1\f$ , \f$s_2\f$ variables 
       *  \f[ \int\int ds_1 ds_2 f(s, s_1,s_2) = 
       *  \int_{s_1^{min}}^{s_1^{max}} ds_1 
       *  \int_{s_2^{min}(s_1)}^{s_2^{max}(s_1)} ds_2 f(s_1,s_2)  \f] 
       *  @param M the overall mass of the system \f$ \sqrt{s} \f$
       *  @param fs the function \f$ f(s_1,s_2)\f$ 
       *  @return the integral over dalitz plot
       */
      double integrate_s1s2 ( const double M , function2 f ) const ;
      // =======================================================================
      /** evaluate the integral over \f$e_2\f$ , \f$e_3\f$ variables 
       *  \f[ \int\int de_2 de_3 f(s,e_2,e_3) = 
       *  \int_{e_2^{min}}^{e_2^{max}} de_2 
       *  \int_{e_3^{min}(e_2)}^{e_3^{max}(e_2)} de_3 f(s,e_2,e_3)  \f] 
       *  @param  M the overall mass of the system \f$ \sqrt{s} \f$
       *  @param  f the function \f$ f(e_2,e_3)\f$ 
       *  @return the integral over dalitz plot
       */
      double integrate_e2e3 ( const double M , function3 f ) const ;
      // =======================================================================
      /** evaluate the integral over \f$e_2\f$ , \f$e_3\f$ variables 
       *  \f[ \int\int de_2 de_3 f(e_2,e_3) = 
       *  \int_{e_2^{min}}^{e_2^{max}} de_2 
       *  \int_{e_3^{min}(e_2)}^{e_3^{max}(e_2)} de_3 f(e_2,e_3)  \f] 
       *  @param  M the overall mass of the system \f$ \sqrt{s} \f$
       *  @param  f the function \f$ f(e_2,e_3)\f$ 
       *  @return the integral over dalitz plot
       */
      double integrate_e2e3 ( const double M , function2 f ) const ;
      // =======================================================================
    private :
      // ======================================================================
      double m_m1 { 0.0 } ;
      double m_m2 { 0.0 } ;
      double m_m3 { 0.0 } ;
      // ======================================================================
    };
    // ========================================================================
  } //                                         The end of namespace Ostap::Math 
  // ==========================================================================
} //                                                 The end of namespace Ostap
// ============================================================================
//                                                                      The END 
// ============================================================================
#endif // OSTAP_DALITZINTEGRAL_H
// ============================================================================
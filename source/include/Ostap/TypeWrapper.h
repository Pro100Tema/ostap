// ============================================================================
#ifndef OSTAP_TYPEWRAPPER_H 
#define OSTAP_TYPEWRAPPER_H 1
// ============================================================================
// Include files 
// ============================================================================
namespace Ostap
{
  // ==========================================================================
  namespace Math
  {
    // ========================================================================
    /** @struct TypeWrapper 
     *  Simple helepr routine to wrap the type 
     *  @author Juan PALACIOS juan.palacios@cern.ch
     *  @date 2006-10-26 
     */    
    template <typename T>
    struct TypeWrapper 
    {
      typedef T value_type;
    } ;
    // ========================================================================
  } //                                             end of namespace Ostap::Math 
  // ==========================================================================
} //                                                     end of namespace Ostap
// ============================================================================
//                                                                      The END 
// ============================================================================
#endif // OSTAP_TYPEWRAPPER_H
// ============================================================================
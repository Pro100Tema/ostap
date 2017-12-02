#!/usr/bin/env python
# -*- coding: utf-8 -*-
# =============================================================================
## @file resolution.py
## Set of useful resolution models:
#  - single Gaussian
#  - double Gaussian                     (gaussian   tails)
#  - symmetric Apolonious                (exponenial tails)
#  - symmetric double-sided Crystal Ball (power-law  tails)
#  @author Vanya BELYAEV Ivan.Belyaeve@itep.ru
#  @date 2017-07-13
# =============================================================================
"""Set of useful resolution models:
- single Gaussian
- double Gaussian                     (gaussian   tails)
- symmetric Apolonious                (exponenial tails)
- symmetric double-sided Crystal Ball (power-law  tails)
"""
# =============================================================================
__version__ = "$Revision:"
__author__  = "Vanya BELYAEV Ivan.Belyaev@itep.ru"
__date__    = "2011-07-25"
__all__     = (
    ##
    'ResoGauss'     , ## simple single-Gaussian resolution model,
    'ResoGauss2'    , ## double-Gaussian resolutin model,
    'ResoApo2'      , ## symmetric Apolonios resolution model,
    'ResoCB2'       , ## symmetric double-sided Crystal Ball resolution model,
    )
# =============================================================================
import ROOT
# =============================================================================
from   ostap.logger.logger import getLogger
if '__main__' ==  __name__ : logger = getLogger ( 'ostap.fitting.resolution' )
else                       : logger = getLogger ( __name__                   )
# =============================================================================
from ostap.fitting.basic import RESOLUTION, makeVar
# =============================================================================    
models = set() 
# =============================================================================
## sigle gaussian model for resolution
# =============================================================================
## @class ResoGauss
#  Trivial single gaussian resolution model
class ResoGauss(RESOLUTION) :
    """Trivial single gaussian resolution model
    """
    def __init__ ( self      ,
                   name      ,   ## the  name 
                   mass      ,   ## the variable 
                   sigma     ,   ## the first sigma 
                   mean  = 0 ) : ## mean-value
        ## initialize the base  
        super(ResoGauss,self).__init__( name  = name  ,
                                        mass  = mass  ,
                                        sigma = sigma ,
                                        mean  = mean  )
        
        ## build gaussian resolution model 
        self.gauss = ROOT.RooGaussModel(
            'ResoGauss_'    + name ,
            'ResoGauss(%s)' % name ,
            self.mass            ,
            self.mean            , 
            self.sigma           )
        
        ## the final PDF 
        self.pdf = self.gauss

models.add ( ResoGauss ) 
# =============================================================================
## @class ResoGauss2
#  Double Gaussian model for  resoltuion
class ResoGauss2(RESOLUTION) :
    """Double-gaussian resolution model
    - sigma of core Gaussian
    - ratio of wide/core widths
    - fraction of core component
    """        
    def __init__ ( self           ,
                   name           ,   ## the name 
                   mass           ,   ## the variable 
                   sigma          ,   ## the core sigma
                   scale    = 1.2 ,   ## sigma2/sigma1 ratio 
                   fraction = 0.5 ,   ## fraction of
                   mean     = 0.0 ) : ## the mean value
        ## initialize the base 
        super(ResoGauss2,self). __init__ ( name  = name  ,
                                           mass  = mass  ,
                                           sigma = sigma ,
                                           mean  = mean  )
        ## fraction of sigma1-component 
        self.fraction = makeVar (
            fraction                   , 
            'CoreFraction_'     + name ,
            'CoreFraction(%s)'  % name , fraction , 0 ,  1 ) 

        ## sigma2/sigma1 width ratio;
        self.scale = makeVar (
            scale ,
            'SigmaScale_'       + name ,
            'SigmaScale(%s)'    % name , scale    , 1 , 10 ) 
        
        from ostap.core.core import Ostap
        self.pdf = Ostap.Models.DoubleGauss (           
            "Reso2Gauss_"       + name ,
            "Reso2Gauss(%s)"    % name ,
            self.mass     ,
            self.sigma    ,
            self.fraction ,
            self.scale    ,
            self.mean    
            )

            
models.add ( ResoGauss2 ) 
# =============================================================================
## @class ResoApo2
#  Symmetrical  Apolonios  model for resolution
class ResoApo2(RESOLUTION) :
    """Symmetric  Apolonios model for resolution
    """
    def __init__ ( self      ,
                   name      ,   ## the  name 
                   mass      ,   ## the variable 
                   sigma     ,
                   beta  = 1 ,   ## the first sigma
                   mean  = 0 ) : ## the mean value 

        ##  initlialize the base 
        super(ResoApo2,self).__init__ ( name  = name  ,
                                        mass  = mass  ,
                                        sigma = sigma ,
                                        mean  = mean  )
        self.beta    = makeVar (
            beta ,
            'ResoBeta_%s'  % name  ,
            'ResoBeta(%s)' % name  , beta , 0.01  , 10000 )
        
        ## build resoltuion model
        from ostap.core.core import Ostap
        self.apo2  = Ostap.Models.Apolonios2 (
            "ResoApolonious_"   + name ,
            "ResoApolonios(%s)" % name ,
            self.mass   ,
            self.mean   ,
            self.sigma  ,
            self.sigma  ,
            self.beta   ) 

        self.pdf = self.apo2
        
        ## 
models.add ( ResoApo2 ) 
# =============================================================================
## @class ResoCB2
#  Symmetrical double-sided Crystal Ball model for resolution
class ResoCB2(RESOLUTION) :
    """Symmetric double-sided Crystal Ball model for resolution
    """
    def __init__ ( self        ,
                   name        ,   ## the  name 
                   mass        ,   ## the  variable 
                   sigma       ,   ## core r esolution
                   alpha = 1.5 ,   ## alpha  
                   n     = 5   ,   ## power-law exponent
                   mean  = 0   ) : ## the mean value

        ## initialize the base 
        super(ResoCB2,self).__init__ ( name  = name  ,
                                       mass  = mass  ,
                                       sigma = sigma ,
                                       mean  = mean  )
            
        self.alpha = makeVar (
            alpha                  ,
            'ResoAlpha_'    + name ,
            'ResoAlpha(%s)' % name , alpha , 0.5   ,  6 )
        
        self.n     = makeVar (
            n                  ,
            'ResoN_'        + name ,
            'ResoN(%s)'     % name , n     , 1.e-6 , 50 )
        
        ## gaussian 
        from ostap.core.core import Ostap
        self.cb2 = Ostap.Models.CrystalBallDS (  
            'ResoCB2_'   + name ,
            'ResoCB2(%s' % name ,
            self.mass           ,
            self.mean           , 
            self.sigma          ,
            self.alpha          ,
            self.n              ,
            self.alpha          ,
            self.n              )
        
        ## the final PDF 
        self.pdf = self.cb2
        
models.add ( ResoCB2 ) 
# =============================================================================
if '__main__' == __name__ :
    
    from ostap.utils.docme import docme
    docme ( __name__ , logger = logger )
    
# =============================================================================
# The END 
# =============================================================================
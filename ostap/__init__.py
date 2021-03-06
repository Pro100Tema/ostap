#!/usr/bin/env python
# -*- coding: utf-8 -*-
# =============================================================================
# Copyright Ostap developers
# =============================================================================
#                                            1.3.3.1
#     .oooooo.                .                        
#    d8P'  `Y8b             .o8                        
#   888      888  .oooo.o .o888oo  .oooo.   oo.ooooo.  
#   888      888 d88(  "8   888   `P  )88b   888' `88b 
#   888      888 `"Y88b.    888    .oP"888   888   888 
#   `88b    d88' o.  )88b   888 . d8(  888   888   888 
#    `Y8bood8P'  8""888P'   "888" `Y888""8o  888bod8P' 
#                                            888       
#                                           o888o      
#                                                    
#  Simple interactive PyRoot-based analysis environment to provide access
#  to zillions useful decorators for ROOT (and not only ROOT!) objects&classes
# 
# - https://github.com/OstapHEP/ostap
# - https://ostaphep.github.io/ostap-tutorials
# - https://github.com/OstapHEP/ostap-tutorials
# 
# =============================================================================
__all__ = (
    'banner',
    'version'
    )
# =============================================================================
## the  actual version of Ostap 
version     = "1.3.3.1"
__version__ = version 
# =============================================================================
##
import ostap.fixes.fixes
# =============================================================================
## Banner
banner = r"""
                                            1.3.3.1
     .oooooo.                .
    d8P'  `Y8b             .o8
   888      888  .oooo.o .o888oo  .oooo.   oo.ooooo.
   888      888 d88(  "8   888   `P  )88b   888' `88b
   888      888 `"Y88b.    888    .oP"888   888   888
   `88b    d88' o.  )88b   888 . d8(  888   888   888
    `Y8bood8P'  8""888P'   "888" `Y888""8o  888bod8P'
                                            888
                                           o888o
                                           
 - https://github.com/OstapHEP/ostap
 - https://ostaphep.github.io/ostap-tutorials
 - https://github.com/OstapHEP/ostap-tutorials
"""
# =============================================================================
##                                                                      The END 
# =============================================================================

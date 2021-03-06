#!/usr/bin/env python
# -*- coding: utf-8 -*-
# =============================================================================
## @file ostap/parallel/parallel_fill.py
#  (parallel) Fill of RooDataSet frmo looong TChain/TTree
#  @author Vanya BELYAEV Ivan.Belyaev@itep.ru
#  @date   2014-09-23
# =============================================================================
"""(parallel) Fill of RooDataSet frmo looong TChain/TTree
"""
# =============================================================================
__version__ = "$Revision$"
__author__  = "Vanya BELYAEV Ivan.Belyaev@itep.ru"
__date__    = "2011-06-07"
__all__     = (
    'pprocess'  , ## paralell processing 
    ) 
# =============================================================================
# logging 
# =============================================================================
from ostap.logger.logger import getLogger 
if '__main__' ==  __name__ : logger = getLogger ( 'ostap.parallel.fill' )
else                       : logger = getLogger ( __name__     )
# =============================================================================
import ROOT
from   ostap.parallel.parallel import Task, WorkManager
# =============================================================================
## The simple task object for more efficient fill of RooDataSet from TChain 
#  @see GaudiMP.Parallel
#  @see GaudiMP.Parallel.Task
#  @see Ostap.SelectorWithVars
#  For 12-core machine, clear speed-up factor of about 8 is achieved 
#  @author Vanya BELYAEV Ivan.Belyaev@itep.ru
#  @date   2014-09-23 
class  FillTask(Task) :
    """The single task object for more efficient fill of RooDataSet from TChain 
    - for 12-core machine, clear speed-up factor of about 8 is achieved 
    """
    ## 
    def __init__ ( self ,  variables , selection , trivial = False ) :
        
        self.variables = variables 
        self.selection = selection 
        self.trivial   = trivial  
        self.output    = ()  

    def initializeLocal   ( self ) : pass
    def initializeRemote  ( self ) : pass

    ## the actual processing 
    def process ( self , item ) :

        import ROOT
        from ostap.logger.logger import logWarning
        with logWarning() :
            import ostap.core.pyrouts            
            import ostap.trees.trees

        
        ## reconstruct chain from the item 
        chain    = item.chain
        ll       = len ( chain )  
        
        first    = item.first
        nevents  = item.nevents 

        all = 0 == first and ( nevents < 0 or ll <= nevents )
        
        if self.trivial and all : 
            import ostap.fitting.selectors
            self.output = chain.make_dataset ( self.variables , self.selection , silent = True ) 
            return

        from   ostap.fitting.selectors import SelectorWithVars
        
        ## use selector  
        selector = SelectorWithVars ( self.variables ,
                                      self.selection ,
                                      silence = True )
        
        args = ()  
        if not all : args  = nevents , first 
            
        num = chain.process ( selector , *args , shortcut = all and self.trivial )
        self.output = selector.data, selector.stat  
        
        if  num < 0 :
            logger.warning ("Processing status %s"  % num )
        
        ##del selector.data
        ##del      selector        
        logger.debug ( 'Processed %s and filled %d entries ' % ( item , len( self.output ) ) )

        del item

    def finalize ( self ) : pass 

    ## merge results/datasets 
    def _mergeResults(self, result) :
        
        if result :
            ds , stat = result
            if not self.output or not self.output[0] :
                self.output = ds , stat  
            else :
                ds_ , stat_ = self.output
                ds_.append ( ds )
                stat_     = list(stat_)
                stat_[0] += stat[0] ## total 
                stat_[1] += stat[1] ## procesed 
                stat_[2] += stat[2] ## skipped                
                self.output = ds_ , tuple(stat_)
                ds.clear () 
            del result            
            logger.debug ( 'Merging: %d entries ' % len( self.output[0] ) )
        else :
            logger.error ( "No valid results for merging" )

            
# ===================================================================================
## parallel processing of loooong chain/tree 
#  @code
#  chain    = ...
#  selector =  ...
#  chain.pprocess ( selector )
#  @endcode 
def pprocess ( chain , selector , nevents = -1 , first = 0 , shortcut = True  , chunk_size = 100000 , ppservers = () , max_files = 10 , silent = False ) :
    """ Parallel processing of loooong chain/tree 
    >>>chain    = ...
    >>> selector =  ...
    >>> chain.pprocess ( selector )
    """
    
    from ostap.trees.trees import Chain

    ch = Chain ( chain ) 

    selection = selector.selection
    variables = selector.variables

    trivial   = selector.trivial_vars and not selector.morecuts 
    
    all = 0 == first and ( 0 > nevents or len ( chain ) <= nevents )
    
    if all and trivial and 1 < len( ch.files ) :
        logger.info ("Configuration is ``trivial'': redefine ``chunk-size'' to -1")
        chunk_size = -1
        
    task  = FillTask ( variables , selection , trivial )
    wmgr  = WorkManager( ppservers = ppservers , silent = silent )
    trees = ch.split ( chunk_size = chunk_size , max_files = max_files )
    wmgr.process( task , trees )
    del trees
    
    dataset, stat = task.output 

    selector.data = dataset
    selector.stat = stat 

    from ostap.logger.logger import attention 
    skipped = 'Skipped:%d' % stat[2]
    skipped = '/' + attention ( skipped ) if stat[2] else ''
    logger.info (
        'Selector(%s): Events Processed:%d/Total:%d%s CUTS: "%s"\n# %s' % (
        selector.name    ,
        stat[1]          ,
        stat[0]          ,
        skipped          ,
        selector.cuts()  , dataset ) )            
    
    return 1 

ROOT.TChain.pprocess = pprocess
ROOT.TTree .pprocess = pprocess

# =============================================================================

_decorated_classes_ = (
    ROOT.TTree  ,
    ROOT.TChain ,    
    )

_new_methods_       = (
    ROOT.TTree .pprocess ,
    ROOT.TChain.pprocess ,
    )

# =============================================================================
if '__main__' == __name__ :
    
    from ostap.utils.docme import docme
    docme ( __name__ , logger = logger )
    
# =============================================================================
# The END 
# =============================================================================

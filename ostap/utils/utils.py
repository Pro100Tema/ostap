#!/usr/bin/env python
# -*- coding: utf-8 -*-
# =============================================================================
## @file
#  Module with some simple but useful utilities for 
#   - timing
#   - memory
#   - profiling
#   - ... 
#
#  It is recommended to install psutil module 
#  @author Vanya BELYAEV Ivan.Belyaev@itep.ru
#  @date   2013-02-10
#  
# =============================================================================
"""Module with some simple but useful utilities for
- timing
- memory
- profiling
- etc

It is recommended to install psutil module 
"""
# =============================================================================
__version__ = "$Revision$"
__author__  = "Vanya BELYAEV Ivan.Belyaev@itep.ru"
__date__    = "2013-02-10"
# =============================================================================
__all__     = (
    #
    'virtualMemory'      , ## context manager to count virtual memory increase 
    'memory'             , ## ditto
    'clocks'             , ## context manager to count clocks 
    'timing'             , ## context manager to count time 
    'timer'              , ## ditto
    'profiler'           , ## context manager to perform profiling
    'rootException'      , ## context manager to perform ROOT Error -> C++/Python exception
    #
    'Profiler'           , ## context manager to perform profiling 
    'RootError2Exception', ## context manager to perform ROOT Error -> C++/Python exception
    ##
    'takeIt'             , ## take and later delete ...
    'isatty'             , ## is the stream ``isatty'' ?
    'with_ipython'       , ## do we run IPython?
    ##
    'batch'              , ## context manager to keep/force certain ROOT ``batch''-mode
    ##
    'keepCanvas'         , ## context manager to keep the current ROOT canvas
    'invisibleCanvas'    , ## context manager to use the invisible current ROOT canvas
    ##
    'keepArgs'           , ## context manager to keep sys.argv
    ##
    'keepCWD'            , ## context manager to keep current working directory 
    ##
    'implicitMT'         , ## context manager to enable/disable implicit MT in ROOT 
    ##
    'Batch'              , ## context manager to keep  ROOT ``batch''-mode
    ##
    'KeepCanvas'         , ## context manager to keep the current ROOT canvas
    'InvisibleCanvas'    , ## context manager to use the invisible current ROOT canvas
    ##
    'KeepArgs'           , ## context manager to keep sys.argv 
    ##
    'ImplicitMT'         , ## context manager to enable/disable implicit MT in ROOT 
    ##
    'counted'            , ## decorator to create 'counted'-function
    ##
    'cmd_exists'         , ## check the existence of the certain command/executable 
   )
# =============================================================================
import ROOT, time, os , sys ## attention here!!
# =============================================================================
from   ostap.logger.logger import getLogger
if '__main__' ==  __name__ : logger = getLogger( 'ostap.utils.utils' )
else                       : logger = getLogger( __name__            )
del getLogger
# =============================================================================
from sys                import version_info  as python_version 
## timing stuff
from ostap.utils.timing import clocks, timing, timer
## other useful stuff 
from ostap.utils.basic  import isatty, with_ipython
## ... and more useful stuff 
from ostap.utils.memory import memory, virtualMemory, Memory 
# =============================================================================

# =============================================================================
## @class Profiler
#  Very simple profiler, based on cProfile module
#  @see https://docs.python.org/2/library/profile.html
#  @code
#  with profiler() :
#      ...  some code here ... 
#  with profiler('output.file') :
#      ...  some code here ... 
#  @endcode
#  @author Vanya Belyaev Ivan.Belyaev@itep.ru
#  @date 2016-07-25                     
class Profiler(object) :
    """Very simple profiler, based on cProfile module
    - see https://docs.python.org/2/library/profile.html
    
    with profiler() :
    #
    # ...  some code here ...
    #

    with profiler( 'output.file' ) :
    #
    # ...  some code here ...
    # 
    """
    def __init__  ( self , fname = '' )  :
        self.fname = fname
        
    ## enter the context
    def __enter__ ( self ) :
        import cProfile as profile
        self._profile = profile.Profile()
        self._profile.enable()
        return self
    
    ## exit the context
    def __exit__ ( self , *_ ) :
        ## end of profiling 
        self._profile.disable()
        
        import pstats
        if self.fname :
            try :
                with open ( self.fname , 'w' ) as out :
                    stat = pstats.Stats( self._profile , stream = out ).sort_stats( 'cumulative' )
                    stat.print_stats()
                del self._profile 
                return 
            except : pass
            
        ## show on screen 
        stat = pstats.Stats( self._profile ).sort_stats( 'cumulative' )
        stat.print_stats()
        del self._profile 
                
# =============================================================================
## Very simple profiler, based on cProfile module
#  @see https://docs.python.org/2/library/profile.html
#  @code
#  with profiler() :
#      ...  some code here ... 
#  @endcode
#  @author Vanya Belyaev Ivan.Belyaev@itep.ru
#  @date 2016-07-25                     
def profiler( name = '' ) :
    """Very simple profiler, based on cProfile module
    - see https://docs.python.org/2/library/profile.html
    
    with profiler() :
    #
    # ...  some code here ...
    # 
    """
    return Profiler ( name )
            

# =============================================================================
## @class NoContext
#  Fake empty context manager to be used as empty placeholder
#  @code
#  with NoContext() :
#  ...  do_something() 
#  @endcode 
#  @author Vanya BELYAEV Ivan.Belyaev@itep.ru
#  date 2013-01-12
class NoContext(object) :
    """Fake (empty) context manager to be used as empty placeholder
    >>> with NoContext() :
    ...         do_something() 
    """
    def __init__  ( self , *args , **kwargs ) : pass
    ## context manager
    def __enter__ ( self         ) : return self 
    ## context manager 
    def __exit__  ( self , *args ) : pass  


# =============================================================================
## @class TakeIt
#  Take some object, keep it and delete at the exit
#  @author Vanya BELYAEV Ivan.Belyaev@itep.ru
#  date 2014-08-03    
class TakeIt(object):
    """Take some object, keep it and delete at the exit
    
    >>> ds = dataset.reduce('pt>1')
    >>> with takeIt ( ds ) :
    ...
    
    """
    def __init__  ( self , other ) :
        self.other = other
        
    def __enter__ ( self ) :
        ROOT.SetOwnership ( self.other , True )
        return self.other
    
    def __exit__  ( self , *args ) :

        o = self.other

        ## delete it! 
        del self.other
        
        if o and hasattr ( o , 'reset'  ) : o.reset  ()
        if o and hasattr ( o , 'Reset'  ) : o.Reset  ()
        if o and hasattr ( o , 'Delete' ) : o.Delete ()
        
        if o : del o
                        
    
# =============================================================================
## Take some object, keep it and delete at the exit
#  @author Vanya BELYAEV Ivan.Belyaev@itep.ru
#  date 2014-08-03    
def takeIt (  other ):
    """Take some object, keep it and delete at the exit
    >>> ds = dataset.reduce('pt>1')
    >>> with takeIt ( ds ) :
    ...    
    """
    return TakeIt ( other ) 

# =============================================================================
## get all open file descriptors
#  The actual code is copied from http://stackoverflow.com/a/13624412
def get_open_fds():
    """Get all open file descriptors    
    The actual code is copied from http://stackoverflow.com/a/13624412
    """
    #
    import resource
    import fcntl
    #
    fds = []
    soft, hard = resource.getrlimit(resource.RLIMIT_NOFILE)
    for fd in range(0, soft):
        try:
            flags = fcntl.fcntl(fd, fcntl.F_GETFD)
        except IOError:
            continue
        fds.append(fd)
    return fds

# =============================================================================
## get the actual file name form file descriptor 
#  The actual code is copied from http://stackoverflow.com/a/13624412
#  @warning: it is likely to be "Linux-only" function
def get_file_names_from_file_number(fds):
    """Get the actual file name from file descriptor 
    The actual code is copied from http://stackoverflow.com/a/13624412 
    """
    names = []
    for fd in fds:
        names.append(os.readlink('/proc/self/fd/%d' % fd))
    return names

# =============================================================================
## helper context manager to activate ROOT Error -> Python exception converter 
#  @see Ostap::Utils::useErrorHandler
#  @see Ostap::Utils::ErrorSentry
#  @code
#  with RootError2Exception() :
#  .... do something here 
#  @endcode 
class RootError2Exception (object) :
    """Helper context manager to activate ROOT Error -> Python exception converter
    #
    with RootError2Exception() :
    ... do something here 
    """
    def __init__ ( self ) :
        import ROOT,cppyy 
        Ostap = cppyy.gbl.Ostap
        self.e_handler  = Ostap.Utils.useErrorHandler 
        self.m_previous = False 

    ## context manager entry point  
    def __enter__ ( self ) :    
        self.m_previous = self.e_handler ( True ) 
        return self
    
    ## context manager exit point
    def __exit__ ( self , *_ ) :    
        if self.m_previous : self.e_handler ( False ) 
        self.m_previous = False 

    def __del__ ( self ) :
        if self.m_previous : self.e_handler ( False ) 
        

# =============================================================================
## helper context manager to activate ROOT Error -> Python exception converter 
#  @see Ostap::Utils::useErrorHandler
#  @see Ostap::Utils::ErrorSentry
#  @code
#  with rootException () :
#  .... do something here 
#  @endcode
def rootException () :
    """Helper context manager to activate ROOT Error -> Python exception converter
    #
    with rootException() :
    ... do something here 
    """
    return RootError2Exception()


# =============================================================================
## context manager to keep ROOT ``batch'' state
#  @code
#  with Batch() :
#  ... do something here 
#  @endcode 
class Batch(object) :
    """Context manager to keep ROOT ``batch'' state
    >>> with Batch() :
    ... do something here 
    """
    def __init__  ( self , batch = True ) :
        self.__batch = batch 
    ## contex manahger: ENTER
    def __enter__ ( self ) :
        import ROOT
        self.old_state = ROOT.gROOT.IsBatch()
        if self.old_state != self.__batch : ROOT.gROOT.SetBatch ( self.__batch ) 
        return self
    ## contex manager: EXIT
    def __exit__  ( self , *_ ) :
        import ROOT
        if self.old_state != ROOT.gROOT.IsBatch() : ROOT.gROOT.SetBatch( self.old_state ) 

# =============================================================================
## context manager to keep ROOT ``batch'' state
#  @code
#  with batch() :
#  ... do something here 
#  @endcode 
def batch( batch = True ) :
    """Context manager to keep ROOT ``batch'' state
    >>> with batch() :
    ... do something here 
    """
    return Batch ( batch )


# =============================================================================
## context manager to keep the current working directory
#  @code
#  with KeepCWD ( new_dir ) :
#    ....
#  @endcode 
class KeepCWD(object) :
    """context manager to keep the current working directory
    >>> with KeepCWD( new_dir ) :
    ...
    """
    def __init__ ( self , new_dir = '' ) :
        self.cwd     = os.getcwd() 
        self.new_dir = new_dir
        
    def __enter__ (  self ) :
        self.cwd = os.getcwd() 
        if self.new_cdir and os.path.exists ( self.new_dir ) and os.path.isdir ( self.new_dir ) :
            os.chdir ( self.new_dir )
            return self
        
    def __exit__ ( self , *_ ) :
        if os.path.exists ( self.cwd ) and os.path.isdir ( self.cwd ) :
            os.chdir ( os.cwd ) 
            
# =============================================================================
## context manager to keep the current working directory
#  @code
#  with keepCWD ( new_dir ) :
#    ....
#  @endcode 
def keepCWD ( new_dir = '' ) :
    """context manager to keep the current working directory
    >>> with keepCWD( new_dir ) :
    ...
    """
    return KeepCWD (  new_dir ) 
        
# =============================================================================
## @class KeepCanvas
#  helper class to keep the current canvas
#  @code
#  with KeepCanvas() :
#  ... do something here 
#  @endcode 
class KeepCanvas(object) :
    """Helper class to keep the current canvas
    >>> with KeepCanvas() :
    ... do something here 
    """
    def __enter__ ( self ) :
        import ROOT 
        self.canvas = ROOT.gPad
    def __exit__  ( self , *_ ) :
        if self.canvas:
            self.canvas.cd()

# =============================================================================
#  Keep the current canvas
#  @code
#  with keepCanvas() :
#  ... do something here 
#  @endcode
def keepCanvas() :
    """Keep the current canvas
    >>> with keepCanvas() :
    ... do something here
    """
    return KeepCanvas()


# =============================================================================
## @class InvisibleCanvas
#  Use context ``invisible canvas''
#  @code
#  with InvisibleCanvas() :
#  ... do somehing here 
#  @endcode
class InvisibleCanvas(KeepCanvas) :
    """Use context ``invisible canvas''
    >>> with InvisibleCanvas() :
    ... do something here 
    """
    ## context manager: ENTER 
    def __enter__ ( self ) :
        ## start from keeping the current canvas 
        KeepCanvas.__enter__ ( self )
        ## create new canvas in batch mode 
        with Batch( True ) : 
            import ROOT 
            self.batch_canvas = ROOT.TCanvas()
            self.batch_canvas.cd ()
            return self.canvas

    ## context manager: EXIT
    def __exit__ ( self , *_ ) :
        if self.batch_canvas :
            self.batch_canvas.Close() 
            del self.batch_canvas             
        KeepCanvas.__exit__ ( self , *_ )

# =============================================================================
## Use context ``invisible canvas''
#  @code
#  with invisibleCanvas() :
#  ... do something here 
#  @endcode
def invisibleCanvas() :
    """ Use context ``invisible canvas''
    >>> with invisibleCanvas() :
    ... do something here 
    """
    return InvisibleCanvas() 


# =============================================================================
## @class KeepArgs
#  context manager to keep/preserve sys.argv
#  @code
#  with KeepArgs() :
#    ...  
#  @endcode 
class KeepArgs(object) :
    """Context manager to keep/preserve sys.argv
    >>> with KeepArgs() :
    ...  
    """
    ## context manager  ENTER 
    def __enter__ ( self ) :
        import sys, copy
        self._args = copy.deepcopy( sys.argv )
        return self
    ## context manager  EXIT
    def __exit__ ( self , *_ ) :
        import sys, copy
        sys.argv = copy.deepcopy ( self._args )
        del self._args 


# =============================================================================
## context manager to keep/preserve sys.argv
#  @code
#  with keepArgs() :
#    ...  
#  @endcode
def keepArgs() :
    """Context manager to keep/preserve sys.argv
    >>> with keepArgs() :
    ...  
    """
    return KeepArgs()


# =============================================================================
## EnableImplicitMT
#  Context manager to enable/disable implicit MT in ROOT 
#  @see ROOT::EnableImplicitMT 
#  @see ROOT::DisableImplicitMT 
#  @see ROOT::IsImplicitMTEnabled
#  @code
#  with ImplicitMT( True ) :
#  ...
#  @endcode
class ImplicitMT(object) :
    """Context manager to enable/disable implicit MT in ROOT 
    >>> with ImplicitMT( True ) :
        ...
    - see ROOT::EnableImplicitMT 
    - see ROOT::DisableImplicitMT 
    - see ROOT::IsImplicitMTEnabled
    """
    def __init__  ( self , enable = True ) :
        self.enable = enable
        
    ## Context manager: ENTER 
    def __enter__ ( self ) :
        self.enabled = ROOT.ROOT. IsImplicitMTEnabled ()
        
        if bool ( self.enabled ) == bool ( self.enable ) : pass 
        elif self.enable : ROOT.ROOT.EnableImplicitMT  ()
        else             : ROOT.ROOT.DisableImplicitMT ()

        return self
    
    ## Context manager: EXIT
    def __exit__ ( self , *_ ) :
        ##
        enabled = ROOT.ROOT.IsImplicitMTEnabled()
        if bool ( enabled ) == bool ( self.enabled ) : pass 
        elif self.enabled : ROOT.ROOT.EnableImplicitMT  ()
        else              : ROOT.ROOT.DisableImplicitMT ()


# =============================================================================
## create 'counted' function to know number of function calls
#  @code
#  fun = ...
#  func = counted ( fun ) ## use as function
# 
#  # alternatively use it as decorator:
#  @counted
#  def fun2 ( ...  ) : return ...
#  @endcode
def counted ( f ):
    """create 'counted' function to know number of function calls

    Example
    -------
    
    >>> fun = ...
    >>> func = counted ( fun ) ## use as function

    >>> @counted
    >>> def fun2 ( ...  ) : return ...
    """
    def wrapped ( *args, **kwargs ):
        wrapped.calls += 1
        return f( *args , **kwargs )
    wrapped.calls = 0
    return wrapped

# =============================================================================
## Context manager to enable/disable implicit MT in ROOT 
#  @see ROOT::EnableImplicitMT 
#  @see ROOT::DisableImplicitMT 
#  @see ROOT::IsImplicitMTEnabled
#  @code
#  with implicitMT( True ) :
#  ...
#  @endcode
def implicitMT ( enable = True ) :
    """Context manager to enable/disable implicit MT in ROOT 
    >>> with implicitMT( True ) :
        ...
    - see ROOT::EnableImplicitMT 
    - see ROOT::DisableImplicitMT 
    - see ROOT::IsImplicitMTEnabled
    """
    return ImplicitMT ( enable ) 


# =============================================================================
## get the command
#  @code
#  >>> if cmd_exists ( 'epstopdf' ) : ... 
#  @endcode 
#  @see https://stackoverflow.com/questions/377017/test-if-executable-exists-in-python
def cmd_exists ( command ) :
    """Check the existence of certain command/executable
    >>> if cmd_exists ( 'epstopdf' ) : ...
    
    """
    if ( python_version.major , python_version.minor ) >= (3,3) : 
        import shutils
        return shutil.which( command ) is not None
    
    return any( os.access ( os.path.join ( path , command  ) , os.X_OK ) for path in os.environ["PATH"].split(os.pathsep) )


# =============================================================================
## @class CleanUp
#  Simple (base) class to get temporary files and directories and to remove them at axit
class  CleanUp(object) :
    
    _tmpfiles = set()
    _tmpdirs  = set()

    @property
    def tmpdir ( self ) :
        """``tmpdir'' : return the name of temporary managed directory
        - the managed directory will be cleaned-up and deleted at-exit
        >>> o    = CleanUp()
        >>> tdir = o.tmpdir 
        """
        tdir = CleanUp.tempdir () 
        return tdir
    
    @property
    def tmpdirs  ( self ) :
        """``tmpdirs'' - list of currently registered managed temporary directories"""
        return tuple ( self._tmpdirs )
    @tmpdirs.setter
    def tmpdirs ( self, values ) :
        if instance ( values , str ) : values = [ values ]
        for o in values :
            if o and isinstance ( o ,  str ) :
                self._tmpdirs.add ( o )
                logger.debug ( 'CleanUp: temporary directory     added %s' % o )
                
    @property 
    def tmpfiles ( self ) :
        """``tempfiles'' : list of registered managed temporary files"""
        return list ( self._tmpfiles ) 
    @tmpfiles.setter
    def tmpfiles ( self , other ) :
        if isinstance ( other , str ) : other = [ other ]
        for o in other :
            if o and isinstance ( o , str ) : 
                self._tmpfiles.add ( o )
                logger.debug ( 'CleanUp: temporary file          added %s' % o )

    @staticmethod
    def tempdir ( suffix = '' , prefix = 'tmp_' ) :
        """Get the name of the temporary directory.
        The directory will be cleaned-up and deleted at-exit.
        >>> dirname = CleanUp.tempdir() 
        """
        import tempfile
        tmp = tempfile.mkdtemp ( suffix = suffix , prefix = prefix ) 
        CleanUp._tmpdirs.add ( tmp )
        logger.debug ( 'CleanUp: temporary directory requested %s' % tmp   )
        return tmp        
    
    @staticmethod
    def tempfile ( suffix = '' , prefix = 'tmp_' , dir = None ) :
        """Get the name of the temporary file. The file will be deleted at-exit
        >>> fname = CleanUp.tempfile() 
        """
        import tempfile, os 
        _file = tempfile.NamedTemporaryFile( suffix = suffix ,
                                             prefix = prefix ,
                                             delete = False  )
        fname = _file.name
        _file.close()
        os.unlink(fname)
        assert not os.path.exists ( fname )
        CleanUp._tmpfiles.add ( fname )
        logger.debug ( 'CleanUp: temporary file      requested %s' % fname )
        return fname


# =============================================================================
import atexit
@atexit.register
def _cleanup_ () :

    ## 1. clean up the files 
    tmp_files  = CleanUp._tmpfiles
    logger.debug ( 'CleanUp: remove temporary files: %s' % list ( tmp_files ) ) 
    while tmp_files :
        f = tmp_files.pop() 
        if os.path.exists ( f ) and os.path.isfile ( f ) :
            logger.verbose ( 'CleanUp: remove temporary file: %s' % f )
            try    : os.remove ( f )
            except : pass

    ## 2. clean up  the directories 
    tmp_dirs = CleanUp._tmpdirs
    logger.debug ( 'CleanUp: remove temporary directories: %s' % list ( tmp_dirs ) ) 
    while tmp_dirs :
        f = tmp_dirs.pop()
        if os.path.exists ( f ) and os.path.isdir ( f ) :
            ## collect all files & subdirectories 
            for root, subdirs, files in os.walk ( f  , topdown = False ):
                ## 2.1 remove all files 
                for ff in files :
                    ff = os.path.join ( root , ff )
                    logger.verbose ( 'CleanUp: remove file %s in temporary directory : %s' %  ( ff , f ) )
                    try    : os.remove  ( ff  )
                    except : pass
                ## 2.2 remove all directories 
                for dd in subdirs :
                    dd = os.path.join ( root , dd )
                    logger.verbose ( 'CleanUp: remove subdirectory %s in temporary directory %s ' % ( dd , f ) )
                    try    : os.rmdir   ( dd  )
                    except : pass 
            ## 2.3 finally remove the root
            logger.debug ( 'CleanUp: remove temporary directory: %s' % f )
            try    : os.rmdir ( f  )
            except : pass

# =============================================================================
if '__main__' == __name__ :
    
    from ostap.utils.docme import docme
    docme ( __name__ , logger = logger )
    
    logger.info ( 80*'*' ) 

            
# =============================================================================
# The END 
# =============================================================================

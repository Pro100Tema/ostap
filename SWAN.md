Ostap installation guide for CERN SWAN service
==============================================
To install the Ostap package on the CERN SWAN service, you must perform the following steps:

1. Run a local session in [CERN SWAN](http://swan.cern.ch/)
2. Go to the terminal and clone the latest released version and build Ostap package

   * git clone —-branch <latest tag> git://github.com/OstapHEP/ostap.git
   * cd ostap
   * mkdir build
   * cd build
   * cmake .. -DCMAKE_INSTALL_PREFIX=<INSTALL_DIRECTORY>
   * make -j8
   * make install
   * source <INSTALL_DIRECTORY>/thisostap.sh
   
 For the latest tag check the page https://github.com/OstapHEP/ostap/releases
 
![Image Terminal](https://github.com/Pro100Tema/SWAN_Image/blob/master/terminal.jpg)

3. Create in local session a shell file in which environment variables for Ostap will be set. The following environment variables must be defined in this file:
```shell
export OSTAPVERSION=1.4.3.1
export OSTAPDIR=$CERNBOX_HOME/ostap/build
export PATH=$OSTAPDIR/bin:$PATH
export PYTHONPATH=$OSTAPDIR/lib/python2.7/site-packages:$PYTHONPATH
export LD_LIBRARY_PATH=$OSTAPDIR/lib:$LD_LIBRARY_PATH
export MANPATH=$MANPATH:$OSTAPDIR/doc/man
```
![Image Shell](https://github.com/Pro100Tema/SWAN_Image/blob/master/ostapenv.jpg)

4. Exit to the start menu of the local session using the button "Change configuration" and in the field “Environment script” add the path to the file created in step 3.

   **For example:** _$CERNBOX_HOME/SWAN_projects/ostapenv.sh_

![Image Config](https://github.com/Pro100Tema/SWAN_Image/blob/master/config.jpg)

5. To use the Ostap package, you need to create a new file and select the Python 2 language.

   To verify the correct installation of the Ostap package on the CERN SWAN, you can use the following code:
   ```python
   import ROOT
   import ostap.fitting.models as Models
   RRV = ROOT.RooRealVar
   c1 = ROOT.TCanvas()
   gauss = Models.Gauss_pdf( 'Gauss' , 
                        xvar  = ( 2.5 , 3.5 ) ,
                        mean  = ( 3.100 , 2.50 , 3.50 ) ,
                        sigma = ( 0.015 , 0.010 , 0.025 ) )
   qq = gauss.draw()
   qq.draw()
   c1.Draw()
   ```
  
The result of the correct operation of the program will be the following image

![Image example](https://github.com/Pro100Tema/SWAN_Image/blob/master/example.jpg)

import os
print os.system('hostname')
#print(os.environ.get('HOME'))
#ppserv = '/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_95/ppft/1.6.4.8/x86_64-centos7-gcc8-opt/bin'
#path = ('/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_95/pathos/0.2.2.1/x86_64-centos7-gcc8-opt/lib/python2.7/site-packages/pathos','/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_95/ppft/1.6.4.8/x86_64-centos7-gcc8-opt/bin')
#os.environ['PATH'] = str(path)
os.environ['HOME']
os.environ['PYTHONPATH']
os.environ['PATH']
os.environ['LD_LIBRARY_PATH']
os.environ.get('LD_PRELOAD')
#print('transfer of environment variables is complete')

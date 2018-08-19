#!/bin/sh -x
HERE=`pwd`
MVT='linear-algebra/kernels/mvt'
threeMM='linear-algebra/kernels/3mm'
FDTD='stencils/fdtd-2d'
DERICHE='medley/deriche'

#cleanup all folders
cd $MVT
./clean.sh
cd $HERE

cd $threeMM
./clean.sh
cd $HERE

cd $FDTD
./clean.sh
cd $HERE

#./$DERICHE
#clean.sh
#cd $HERE



#build all files to get ready for the runs
cd $MVT
./build.sh
cd $HERE

cd $threeMM
./build.sh
cd $HERE

cd $FDTD
./build.sh
cd $HERE

#cd $DERICHE
#./build.sh
#cd $HERE



#run everything
echo "##################################################"
echo "### run mvt"
echo "##################################################"
echo ""
echo "----------------- without tiling -----------------"
cd $MVT
./execute.sh
echo "------------------ with tiling -------------------"
./execute-with-tiling.sh
echo ""
echo ""
cd $HERE

echo "##################################################"
echo "### run 3mm"
echo "##################################################"
echo ""
echo "----------------- without tiling -----------------"
cd $threeMM
./execute.sh
echo "------------------ with tiling -------------------"
./execute-with-tiling.sh
echo ""
echo ""
cd $HERE

echo "##################################################"
echo "### run fdtd-2d"
echo "##################################################"
echo ""
echo "----------------- without tiling -----------------"
cd $FDTD
./execute.sh
echo "------------------ with tiling -------------------"
./execute-with-tiling.sh
echo ""
echo ""
cd $HERE

#echo "##################################################"
#echo "### run deriche"
#echo "##################################################"
#echo ""
#./$DERICHE
#./execute.sh
#cd $HERE

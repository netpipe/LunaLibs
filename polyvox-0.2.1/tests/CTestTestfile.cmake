# CMake generated Testfile for 
# Source directory: /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests
# Build directory: /home/Dev/libs/csg-stuff/polyvox-0.2.1/tests
# 
# This file includes the relevent testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(PythonSurfaceExtractorTest "python" "/home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/TestSurfaceExtractor.py")
ADD_TEST(AmbientOcclusionGeneratorExecuteTest "/home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/TestAmbientOcclusionGenerator" "testExecute")
ADD_TEST(ArrayReadWriteTest "/home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/TestArray" "testReadWrite")
ADD_TEST(AStarPathfinderExecuteTest "/home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/TestAStarPathfinder" "testExecute")
ADD_TEST(CubicSurfaceExtractorExecuteTest "/home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/TestCubicSurfaceExtractor" "testExecute")
ADD_TEST(LowPassFilterExecuteTest "/home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/TestLowPassFilter" "testExecute")
ADD_TEST(VolumeSizeTest "/home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/testvolume" "testSize")
ADD_TEST(MaterialTestCompile "/home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/testmaterial" "testCompile")
ADD_TEST(RaycastExecuteTest "/home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/TestRaycast" "testExecute")
ADD_TEST(RegionEqualityTest "/home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/TestRegion" "testEquality")
ADD_TEST(SurfaceExtractorExecuteTest "/home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/TestSurfaceExtractor" "testExecute")
ADD_TEST(VectorLengthTest "/home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/testvector" "testLength")
ADD_TEST(VectorDotProductTest "/home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/testvector" "testDotProduct")
ADD_TEST(VectorEqualityTest "/home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/testvector" "testEquality")
ADD_TEST(VolumeSubclassExtractSurfaceTest "/home/Dev/libs/csg-stuff/polyvox-0.2.1/tests/TestVolumeSubclass" "testExtractSurface")

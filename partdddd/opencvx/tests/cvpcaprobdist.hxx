#ifdef _MSC_VER
#pragma warning(disable:4996)
#pragma comment(lib, "cv.lib")
#pragma comment(lib, "cxcore.lib")
#pragma comment(lib, "cvaux.lib")
#pragma comment(lib, "highgui.lib")
#endif

#include <stdio.h>
#include <stdlib.h>
#include "cv.h"
#include "cvaux.h"
#include "cxcore.h"
#include "highgui.h"
#include "cvpcaprobdist.h"
#include "cvxmat.h"

#include <cxxtest/TestSuite.h>

class CvPcaDistTest : public CxxTest::TestSuite
{
public:
    void testPcaProbDist()
    {
        int D = 4, N = 3;
        double a[] = { 
            0.4854,    0.9157,    0.0357,
            0.8003,    0.7922,    0.8491,
            0.1419,    0.9595,    0.9340,
            0.4218,    0.6557,    0.6787
        };
        CvMat mat = cvMat( D, N, CV_64FC1, a ); // 64FC1 for double
        CvMat *avg = cvCreateMat( D, 1, CV_64FC1 );
        CvMat *eigenvalues = cvCreateMat( MIN(D,N-1), 1, CV_64FC1 );
        CvMat *eigenvectors = cvCreateMat( MIN(D, N-1), D, CV_64FC1 );
        cvCalcPCA( &mat, avg, eigenvalues, eigenvectors, CV_PCA_DATA_AS_COL );
        
        double b[] = { 
            0.478933, 0,
            0.813867, 0,
            0.678467, 0,
            0.585400, 0
        };
        N = 2;
        CvMat mat2 = cvMat( D, N, CV_64FC1, b );
        CvMat *probs = cvCreateMat( 1, N, CV_64FC1 );
        cvMatPcaProbDist( &mat2, avg, eigenvectors, 1.0, probs, 1, false );

        TS_ASSERT_DELTA( cvmGet( probs, 0, 0 ), 0.398942, 0.00001 );
        TS_ASSERT_DELTA( cvmGet( probs, 0, 1 ), 0.264696, 0.00001 );
    }
};

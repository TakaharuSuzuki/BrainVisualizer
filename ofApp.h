#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofTrueTypeFont mFont;
		
		char* mText[50];
		
		float* mSignalData;
		int mSignalNum;

		float mWidth, mHeight;
		int mVisualUpdateHz;
		int mFontSize;
		float mCenter[3][2];
		float mXY[8][2];
		int mComponentNum, mFrequencyNum, mPercentNum;
		float mRadius;
		float mPos[11][2];
		int mTextBox[50][2];
		int mPolygonColor[8][4];
		int mPolygonCurrentColor[4];
		int mRectangleColor[10][3];
		
		float mWillAngle[2];
		float mWillPolygon[8][2];
		int mWillRectangle[10];
		int mWillMax;
		int mWillTransparency[2];
		
		float mIsAngle[2];
		int mIsTriangle[6][2];
		float mIsPolygon[8][2];
		int mIsPolygonBlur[8][20][2];
		int mIsRectangle[10];
		int mIsTransparency[2];
		
		float mWasAngle[2];
		float mWasPolygon[8][2];
		int mWasRectangle[10];
		int mWasMax;
		int mWasTransparency[2];

		float mTime;
		float mSinceLastFrame;
		float mElapsedTime;
		int mPass;
		
		ofxTCPClient mTCP;
		string mMessage;
		float mConnectTime;
		float mDeltaTime;
		bool mIsConnected;
		int mMatlabValue[20];
};

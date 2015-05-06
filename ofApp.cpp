#include "ofApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	// for statement
	int i, j;
	ofRectangle rect;
	
	// Interface
	ofSetWindowTitle("EEG Visualizer");
	ofBackground(0,0,0);
	ofEnableSmoothing();
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetCircleResolution(256);
	ofEnableAlphaBlending();
	mVisualUpdateHz	=	1;
	mHeight			=	ofGetHeight();
	mWidth			=	ofGetWidth();
	mTime 			=	0;
	mSinceLastFrame	=	0;
	mPass;
	
	// Font
	if (mHeight <= mWidth){
		mFontSize	=	int(mHeight/50);}
	else if (mHeight > mWidth){
		mFontSize	=	int(mWidth/50);
	}
	mFont.loadFont("ARLRDBD.ttf",mFontSize);
	
	// Number
	mComponentNum	=	8;
	mFrequencyNum	=	10;
	mPercentNum		=	11;
	mSignalNum		=	500;

	// Signal data
	mSignalData = new float[mSignalNum];
	for (int i=0;i<mSignalNum;i++){
		mSignalData[i] = 0; 
	} 
	
	// Ellipse [0] and Circle [1],[2] centre
	mCenter[0][0]	=	5*mWidth/20;
	mCenter[0][1]	=	5*mHeight/10;
	mCenter[1][0]	=	12*mWidth/20;
	mCenter[1][1]	=	7.5*mHeight/10;
	mCenter[2][0]	=	17.2*mWidth/20;
	mCenter[2][1]	=	7.5*mHeight/10;
	
	// Ellipse vertex 
	for (i=0;i<mComponentNum;i++){
		mXY[i][0]	=	cos((90-45*i)*PI/180)*3.7*mWidth/20;
		mXY[i][1]	=	sin((90-45*i)*PI/180)*3.7*mHeight/10;
	}
	
	// Circle radius and vertex
	if (2*mHeight/10 < 2*mWidth/20){
		mRadius		=	2*mHeight/10;}
	else{
		mRadius		=	2*mWidth/20;
	} 

	for (i=0;i<mPercentNum;i++){
		mPos[i][0]	=	cos((225-27*i)*PI/180)*mRadius;
		mPos[i][1]	=	-sin((225-27*i)*PI/180)*mRadius;
	}

	// Text
	mText[0]		=	"Delta";
	mText[1]		=	"Theta";
	mText[2]		=	"Low";
	mText[3]		=	"Alpha";
	mText[4]		=	"High";
	mText[5]		=	"Alpha";
	mText[6]		=	"Low";
	mText[7]		=	"Beta";
	mText[8]		=	"High";
	mText[9]		=	"Beta";
	mText[10]		=	"Low";
	mText[11]		=	"Gamma";
	mText[12]		=	"High";
	mText[13]		=	"Gamma";
	mText[14]		=	"0";
	mText[15]		=	"5";
	mText[16]		=	"10";
	mText[17]		=	"15";
	mText[18]		=	"20";
	mText[19]		=	"25";
	mText[20]		=	"30";
	mText[21]		=	"35";
	mText[22]		=	"40";
	mText[23]		=	"45";
	mText[24]		=	"50";
	mText[25]		=	"Hz";
	mText[26]		=	"0";
	mText[27]		=	"10";
	mText[28]		=	"20";
	mText[29]		=	"30";
	mText[30]		=	"40";
	mText[31]		=	"50";
	mText[32]		=	"60";
	mText[33]		=	"70";
	mText[34]		=	"80";
	mText[35]		=	"90";
	mText[36]		=	"100";
	mText[37]		=	"ATTENTION";
	mText[38]		=	"0";
	mText[39]		=	"10";
	mText[40]		=	"20";
	mText[41]		=	"30";
	mText[42]		=	"40";
	mText[43]		=	"50";
	mText[44]		=	"60";
	mText[45]		=	"70";
	mText[46]		=	"80";
	mText[47]		=	"90";
	mText[48]		=	"100";
	mText[49]		=	"MEDITATION";

	// Bounding box
	for (i=0;i<50;i++){
		rect 					= 	mFont.getStringBoundingBox(mText[i],0,0);
		mTextBox[i][0] 			= 	rect.width;
		mTextBox[i][1] 			= 	rect.height;
	}

	// Triangle vertex position
	for (i=0;i<6;i++){
		mIsTriangle[i][0]		=	0;
		mIsTriangle[i][1]		=	0;
	}

	for (i=0;i<2;i++){
		mWillAngle[i]			=	0;
		mIsAngle[i]				=	0;
		mWasAngle[i]			=	0;
	}
	
	// Polygon vertex position
	for (i=0;i<mComponentNum;i++){
		mWillPolygon[i][0]		=	mCenter[0][0];
		mWillPolygon[i][1]		=	mCenter[0][1];
		mIsPolygon[i][0]		=	mCenter[0][0];
		mIsPolygon[i][1]		=	mCenter[0][1];
		mWasPolygon[i][0]		=	mCenter[0][0];
		mWasPolygon[i][1]		=	mCenter[0][1];
	}

	// Polygon blur vertex
	for (i=0;i<mComponentNum;i++){
		for (j=0;j<20;j++){
			mIsPolygonBlur[i][j][0] = mCenter[0][0];
			mIsPolygonBlur[i][j][1] = mCenter[0][1];}
	}

	// Number of Rectangle number
	for (i=0;i<mFrequencyNum;i++){
		mWillRectangle[i]		=	0;
		mIsRectangle[i]			=	0;
		mWasRectangle[i]		=	0;
	}
	
	// Transparency
	for (i=0;i<2;i++){
		mWillTransparency[i]	=	0;
		mIsTransparency[i]		=	0;
		mWasTransparency[i]		=	0;
	}
	
	// Polygon maximum Number
	mWillMax					=	0;
	mWasMax 					= 	0;

	// Polygon Color
	mPolygonColor[0][0]			=	255;
	mPolygonColor[0][1]			=	0;
	mPolygonColor[0][2]			=	0;
	mPolygonColor[0][3]			=	25;
	mPolygonColor[1][0]			=	255;
	mPolygonColor[1][1]			=	127;
	mPolygonColor[1][2]			=	0;
	mPolygonColor[1][3]			=	25;
	mPolygonColor[2][0]			=	255;
	mPolygonColor[2][1]			=	255;
	mPolygonColor[2][2]			=	0;
	mPolygonColor[2][3]			=	25;
	mPolygonColor[3][0]			=	127;
	mPolygonColor[3][1]			=	255;
	mPolygonColor[3][2]			=	0;
	mPolygonColor[3][3]			=	25;
	mPolygonColor[4][0]			=	0;
	mPolygonColor[4][1]			=	255;
	mPolygonColor[4][2]			=	127;
	mPolygonColor[4][3]			=	25;
	mPolygonColor[5][0]			=	0;
	mPolygonColor[5][1]			=	255;
	mPolygonColor[5][2]			=	255;
	mPolygonColor[5][3]			=	25;
	mPolygonColor[6][0]			=	0;
	mPolygonColor[6][1]			=	0;
	mPolygonColor[6][2]			=	255;
	mPolygonColor[6][3]			=	25;
	mPolygonColor[7][0]			=	127;
	mPolygonColor[7][1]			=	0;
	mPolygonColor[7][2]			=	255;
	mPolygonColor[7][3]			=	25;

	mPolygonCurrentColor[0]		=	0;
	mPolygonCurrentColor[1]		=	0;
	mPolygonCurrentColor[2]		=	0;
	mPolygonCurrentColor[3]		=	0;

	// Rectangle Color
	mRectangleColor[0][0]		=	255;
	mRectangleColor[0][1]		=	0;
	mRectangleColor[0][2]		=	0;
	mRectangleColor[1][0]		=	255;
	mRectangleColor[1][1]		=	127;
	mRectangleColor[1][2]		=	0;
	mRectangleColor[2][0]		=	255;
	mRectangleColor[2][1]		=	255;
	mRectangleColor[2][2]		=	0;
	mRectangleColor[3][0]		=	127;
	mRectangleColor[3][1]		=	255;
	mRectangleColor[3][2]		=	0;
	mRectangleColor[4][0]		=	0;
	mRectangleColor[4][1]		=	127;
	mRectangleColor[4][2]		=	0;
	mRectangleColor[5][0]		=	0;
	mRectangleColor[5][1]		=	255;
	mRectangleColor[5][2]		=	127;
	mRectangleColor[6][0]		=	0;
	mRectangleColor[6][1]		=	255;
	mRectangleColor[6][2]		=	255;
	mRectangleColor[7][0]		=	0;
	mRectangleColor[7][1]		=	0;
	mRectangleColor[7][2]		=	255;
	mRectangleColor[8][0]		=	127;
	mRectangleColor[8][1]		=	0;
	mRectangleColor[8][2]		=	255;
	mRectangleColor[9][0]		=	255;
	mRectangleColor[9][1]		=	0;
	mRectangleColor[9][2]		=	255;
	
	// TCP Client
	mIsConnected = mTCP.setup("127.0.0.1",11999);
	mTCP.setMessageDelimiter("\n");
	mConnectTime = 0;
	mDeltaTime = 0;
	for (i=0;i<20;i++){
		mMatlabValue[i] = 30;		// 0-7 polygon, 8-17 rectangle, 18 attention, 19 meditation
	}
}

//--------------------------------------------------------------
void testApp::update(){

	// Updater
	int sizeUpdater 	= 	0;		// to check if the windows size is changed
	int maxUpdater 		= 	0;		// to check the maximum polygon number
	int visualUpdater	=	0;		// to check visual feedback, not interpolation
	
	// for statement
	int i, j;
	float t;
	ofRectangle rect;
	
	// Time
	mSinceLastFrame 	= 	ofGetLastFrameTime();
	mTime 				+= 	mSinceLastFrame;

	if (mTime > 1/mVisualUpdateHz){
		mTime 			= 	0;
		visualUpdater	=	1;
	}
	float current		=	mTime/mVisualUpdateHz;
	int pass			=	1;
	if (int(mSinceLastFrame*mSignalNum)>1){
		pass			=   int(mSinceLastFrame*mSignalNum);
	}
	mPass				+=	pass;
	if (mPass>mSignalNum){
		mPass			=	mPass%mSignalNum;
	}

	// Changing window size
	if (mWidth != ofGetWidth() || (mHeight != ofGetHeight())){
		mWidth 			= 	ofGetWidth();
		mHeight 		= 	ofGetHeight();
		sizeUpdater 	= 	1;
	}
	
	// Changing font size
	if (sizeUpdater == 1){
		if (mHeight <= mWidth){
			mFontSize 	= 	int(mHeight/60);}
		else if (mHeight > mWidth){
			mFontSize 	= 	int(mWidth/60);}
		mFont.loadFont("ARLRDBD.ttf",mFontSize);
	}

	// Changing ellipse size
	if (sizeUpdater == 1){
		mCenter[0][0] 	= 	5*mWidth/20;
		mCenter[0][1] 	= 	5*mHeight/10;
		for (i=0;i<mComponentNum;i++){
			mXY[i][0] 	= 	-sin((180-45*i)*PI/180)*3.7*mWidth/20;
			mXY[i][1] 	= 	cos((180-45*i)*PI/180)*3.7*mHeight/10;}
	}

	// Changing circle size and radius
	if (sizeUpdater == 1){
		if (2*mHeight/10 < 2*mWidth/20){
			mRadius 	= 	2*mHeight/10;}
		else{
			mRadius 	= 	2*mWidth/20;}
		
		mCenter[1][0] 	= 	12*mWidth/20;
		mCenter[1][1] 	= 	7.5*mHeight/10;
		mCenter[2][0] 	= 	17.2*mWidth/20;
		mCenter[2][1] 	= 	7.5*mHeight/10;
		for (i=0;i<mPercentNum;i++){
			mPos[i][0] 	= 	cos((225-27*i)*PI/180)*mRadius;
			mPos[i][1] 	= 	-sin((225-27*i)*PI/180)*mRadius;}
	}		
	
	// Changing bounding box
	if (sizeUpdater == 1){
		for (i=0;i<50;i++){
				rect 	= 	mFont.getStringBoundingBox(mText[i],0,0);
				mTextBox[i][0] 	=	rect.width;
				mTextBox[i][1] 	=	rect.height;}
	}
	
	// TCP communication
	if (mIsConnected){
	string str				= mTCP.receive();
		if (str.length()>0){
			mMessage			=	str;
			vector<string> strPnt =	ofSplitString(mMessage,"|");
			for (i=0;i<strPnt.size();i++){
				mMatlabValue[i] =	atof(strPnt[i].c_str());}}
		}
	else{
		mDeltaTime = ofGetElapsedTimeMillis() - mConnectTime;
		if (mDeltaTime > 5000){
			mIsConnected		=	mTCP.setup("127.0.0.1",11999);
			mConnectTime		=	ofGetElapsedTimeMillis();}
	}
	
	// Update triangle and transparency
	if (visualUpdater == 1){
		for (i=0;i<2;i++){
			mWasAngle[i]		=	mWillAngle[i];
			mWasTransparency[i]	=	mWillTransparency[i];
		}
		
		for  (i=0;i<2;i++){
			//t = ofRandom(-45, 225);
			t = mMatlabValue[i+18];
			mWillAngle[i]			=	t;
			mWillTransparency[i] 	=	int(100*(225-t)/270);}
	}

	//Update polygon
	if (visualUpdater == 1){
		mWasMax 				=	mWillMax;
		for (i=0;i<mComponentNum;i++){
			//t = ofRandom(30, 90);
			t = mMatlabValue[i];
		
			if (t != 0){
				if (maxUpdater<t){
					maxUpdater 	=	t;
					mWillMax 	=	i;}}
			else{
				maxUpdater 		=	t;
				mWillMax 		=	i;}

			mWasPolygon[i][0]	=	mWillPolygon[i][0];
			mWillPolygon[i][0]	=	mCenter[0][0]+mXY[i][0]*t/100;
			mWasPolygon[i][1]	=	mWillPolygon[i][1];
			mWillPolygon[i][1]	=	mCenter[0][1]+mXY[i][1]*t/100;}
	}

	// Update rectangle number
	if (visualUpdater == 1){
		for (i=0;i<mFrequencyNum;i++){
			mWasRectangle[i]	=	mWillRectangle[i];
			//t = ofRandom(0, 40);
			t = mMatlabValue[i+8];
			mWillRectangle[i] 	=	int(t);}
	}
	
	// Calculate current triangle and transparency
	for (i=0;i<2;i++){
		mIsAngle[i]				=	mWasAngle[i]+current*(mWillAngle[i]-mWasAngle[i]);
		mIsTransparency[i]		=	mWasTransparency[i]+current*(mWillTransparency[i]-mWasTransparency[i]);

		mIsTriangle[3*i][0]		=	int(mCenter[i+1][0]+cos(mIsAngle[i]*PI/180)*mRadius);
		mIsTriangle[3*i][1]		=	int(mCenter[i+1][1]-sin(mIsAngle[i]*PI/180)*mRadius);
		mIsTriangle[3*i+1][0]	=	int(mCenter[i+1][0]+cos((mIsAngle[i]+90)*PI/180)*mRadius/8);
		mIsTriangle[3*i+1][1]	=	int(mCenter[i+1][1]-sin((mIsAngle[i]+90)*PI/180)*mRadius/8);
		mIsTriangle[3*i+2][0]	=	int(mCenter[i+1][0]+cos((mIsAngle[i]-90)*PI/180)*mRadius/8);
		mIsTriangle[3*i+2][1]	=	int(mCenter[i+1][1]-sin((mIsAngle[i]-90)*PI/180)*mRadius/8);
	}

	// Calculate current Polygon position, blur and colour
	for (i=0;i<mComponentNum;i++){
		mIsPolygon[i][0]		=	mWasPolygon[i][0]+current*(mWillPolygon[i][0]-mWasPolygon[i][0]);
		mIsPolygon[i][1]		=	mWasPolygon[i][1]+current*(mWillPolygon[i][1]-mWasPolygon[i][1]);
	}

	for (i=0;i<mComponentNum;i++){
		for (j=0;j<20;j++){
			if (j == 19){
				mIsPolygonBlur[i][j][0] =	mIsPolygon[i][0];
				mIsPolygonBlur[i][j][1] =	mIsPolygon[i][1];}			
			else{
				mIsPolygonBlur[i][j][0] =	mIsPolygonBlur[i][j+1][0];
				mIsPolygonBlur[i][j][1] =	mIsPolygonBlur[i][j+1][1];}}
	}

	for (i=0;i<4;i++){
		mPolygonCurrentColor[i]	=	int(mPolygonColor[mWasMax][i]+current*(mPolygonColor[mWillMax][i]-mPolygonColor[mWasMax][i]));
	}
	
	// Calculate current rectangle number
	for (i=0;i<mFrequencyNum;i++){
		mIsRectangle[i]			=	int(mWasRectangle[i]+current*(mWillRectangle[i]-mWasRectangle[i]));
	}

	// Update Signal 
	for (i=mSignalNum-1;i>pass-1;i--){
		mSignalData[i] = mSignalData[i-pass+1];
	}
	for (i=0;i<pass;i++){
		mSignalData[i] = sin(2*PI*(mPass-i)/mSignalNum);
	}
}

//--------------------------------------------------------------
void testApp::draw(){

	// for statement
	int i, j=0;
	ofPolyline signal;

	// Band text
	ofSetColor(255,255,255);
	for (i=0;i<mComponentNum+6;i++){
		if (i==2 || i==4 || i==6 || i==8 || i==10 || i==12){
		mFont.drawString(	mText[i],	mCenter[0][0]+mXY[i-j][0]-mTextBox[i][0]/2, mCenter[0][1]+mXY[i-j][1]-1.2*mTextBox[i][1]);
		j++;}
		else{
			mFont.drawString(	mText[i],	mCenter[0][0]+mXY[i-j][0]-mTextBox[i][0]/2,	mCenter[0][1]+mXY[i-j][1]);}
	}

	// Attention text
	for (i=0;i<mPercentNum+1;i++){
		if (i==mPercentNum){
			mFont.drawString(	mText[26+i],	mCenter[1][0]-mTextBox[26+i][0]/2,	mCenter[1][1]+mRadius);}
		else{
			mFont.drawString(	mText[26+i],	mCenter[1][0]+mPos[i][0]-mTextBox[26+i][0]/2,	mCenter[1][1]+mPos[i][1]);}
	}
	
	// Meditation text
	for (i=0;i<mPercentNum+1;i++){
		if (i==mPercentNum){
			mFont.drawString(	mText[38+i],	mCenter[2][0]-mTextBox[38+i][0]/2,	mCenter[2][1]+mRadius);}
		else{
			mFont.drawString(	mText[38+i],	mCenter[2][0]+mPos[i][0]-mTextBox[38+i][0]/2,	mCenter[2][1]+mPos[i][1]);}
	}
	
	// Frequency text
	for (i=0;i<mFrequencyNum+2;i++){
		if (i==mFrequencyNum+1){
			mFont.drawString(	mText[14+i],	int(19.6*mWidth/20)-mTextBox[14+i][0]/2,	int(4.8*mHeight/10));}
		else{
			mFont.drawString(	mText[14+i],	int((10.1+0.9*i)*mWidth/20)-mTextBox[14+i][0]/2,	int(4.8*mHeight/10));}
	}

	// Attention appearance	
	for (i=0;i<100;i++){
		ofSetColor(0,2*i,0,i);
		ofCircle(	mCenter[1][0],	mCenter[1][1],	mRadius/2 + (100-i)*mRadius*mIsTransparency[0]/100/100/2);
	}
		
	ofSetColor(255,0,0);
	ofTriangle(mIsTriangle[0][0],	mIsTriangle[0][1],	mIsTriangle[1][0],	mIsTriangle[1][1],	mIsTriangle[2][0],	mIsTriangle[2][1]);
	ofSetColor(0,0,0);
	ofCircle(	mCenter[1][0],	mCenter[1][1],	mRadius/2);
	ofSetColor(0,255*mIsTransparency[0]/100,0);
	ofCircle(	mCenter[1][0],	mCenter[1][1],	mRadius/4);

	// Meditation appearance
	for (i=0;i<100;i++){
		ofSetColor(0,2*i,0,i);
		ofCircle(	mCenter[2][0],	mCenter[2][1],	mRadius/2 + (100-i)*mRadius*mIsTransparency[1]/100/100/2);
	}

	ofSetColor(255,0,0);
	ofTriangle(mIsTriangle[3][0],	mIsTriangle[3][1],	mIsTriangle[4][0],	mIsTriangle[4][1],	mIsTriangle[5][0],	mIsTriangle[5][1]);
	ofSetColor(0,0,0);
	ofCircle(	mCenter[2][0],	mCenter[2][1],	mRadius/2);
	ofSetColor(0,255*mIsTransparency[1]/100,0);
	ofCircle(	mCenter[2][0],	mCenter[2][1],	mRadius/4);

	//polygon appearance
	for (i=0;i<mComponentNum;i++){
		for (j=0;j<20;j++){
			ofSetLineWidth(10-j/2);
			ofSetColor(j*mPolygonCurrentColor[0]/10,j*mPolygonCurrentColor[1]/10,j*mPolygonCurrentColor[2]/10,j*mPolygonCurrentColor[3]);
			if (i==mComponentNum-1){
				ofLine(mIsPolygonBlur[i][j][0],	mIsPolygonBlur[i][j][1],	mIsPolygonBlur[0][j][0],	mIsPolygonBlur[0][j][1]);}
			else{
				ofLine(mIsPolygonBlur[i][j][0],	mIsPolygonBlur[i][j][1],	mIsPolygonBlur[i+1][j][0],	mIsPolygonBlur[i+1][j][1]);}}
	}

	// Rectangle appearance
	for (i=0;i<mFrequencyNum;i++){
		for (j=0;j<mIsRectangle[i];j++){
			ofSetColor(mRectangleColor[i][0],mRectangleColor[i][1],mRectangleColor[i][2],255);
			ofRect(int((10.3+0.9*i)*mWidth/20), int(4.5*mHeight/10)-int(4*mHeight*j/10/40),int(0.6*mWidth/20),int(2*mHeight/10/40));}
	}

	// Signal appearance
	ofSetColor(251,218,222,100);
	ofSetLineWidth(10);
	for (int i=0; i<mSignalNum; i++){
		float px = 1*mWidth/20+8*mWidth*i/mSignalNum/20;
		float py = 2*mHeight*mSignalData[i]/10+7.5*mHeight/10;
		signal.addVertex(ofVec2f(px,py));
	}
	signal.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
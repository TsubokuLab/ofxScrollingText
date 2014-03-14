//
//  ofxScrollingText.cpp
//
//  Created by Teruaki Tsubokura on 2014/03/13.
//
//

#include "ofxScrollingText.h"

//--------------------------------------------------------------
ofxScrollingText *ofxScrollingText::mIns = 0;
ofxScrollingText* ofxScrollingText::instance(){
    if(!mIns){
        mIns = new ofxScrollingText();
    }
    return mIns;
}

//--------------------------------------------------------------
ofxScrollingText::ofxScrollingText(){
    isVisible = false;
    isPlaying = false;
    isScroll = true;
    fontColor = ofColor(255,255,255,255);
    bgColor = ofColor(30, 30, 30, 180);
    speed = 17.0;
    alpha = 0;
    textString = "";
    textPosition.y = ofGetHeight() * 0.8;
    width = ofGetWidth();
    height = ofGetHeight()/10;
}

//--------------------------------------------------------------
ofxScrollingText::~ofxScrollingText(){
    
}

//--------------------------------------------------------------
void ofxScrollingText::setup(string _fontPath, int _fontSize){
    font.loadFont(_fontPath, _fontSize, true, true);
    height = _fontSize * 2;
}

//--------------------------------------------------------------
void ofxScrollingText::update(){
    width = ofGetWidth();
    textPosition.y = ofGetHeight() - height;
    if(isVisible && textString != ""){
        if( alpha < 1) alpha += (1 - alpha) * 0.1;
        if(isScroll){
            if(0 < textPosition.x + font.stringWidth(textString)){
                textPosition.x -= speed;
            }else{
                isVisible = false;
            }
        }else{
            textPosition.x = ofGetWidth() / 2 - font.stringWidth(textString) / 2;
        }
    }else{
        if( alpha > 0.01){
            alpha += (0 - alpha) * 0.1;
        }else{
            alpha = 0;
            if(isPlaying){
                isPlaying = false;
                cout << "[ofxScrollingText] completeEvent." << endl;
                ofNotifyEvent(ofxScrollingText::completeEvent);
            }
        }
    }
}

//--------------------------------------------------------------
void ofxScrollingText::draw(){
    ofPushStyle();
    ofSetColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a * alpha);
    ofRect(0, textPosition.y, width, height);
    ofSetColor(fontColor.r, fontColor.g, fontColor.b, fontColor.a * alpha);
    font.drawString(textString, textPosition.x, textPosition.y + height - (height - font.stringHeight(textString))/2);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofxScrollingText::showText(string _message){
    if(_message != ""){
        textString = _message;
        isVisible = true;
        isPlaying = true;
        textPosition.x = ofGetWidth();
    }
}

//--------------------------------------------------------------
void ofxScrollingText::hideText(){
    isVisible = false;
}

//--------------------------------------------------------------
bool ofxScrollingText::getVisible(){
    return isVisible;
}

//--------------------------------------------------------------
void ofxScrollingText::setFontColor(ofColor _color){
    fontColor = _color;
}

//--------------------------------------------------------------
ofColor ofxScrollingText::getFontColor(){
    return fontColor;
}

//--------------------------------------------------------------
void ofxScrollingText::setBackgroundColor(ofColor _color){
    bgColor = _color;
}

//--------------------------------------------------------------
ofColor ofxScrollingText::getBackgroundColor(){
    return bgColor;
}

//--------------------------------------------------------------
void ofxScrollingText::setSpeed(float _speed){
    speed = _speed;
}

//--------------------------------------------------------------
float ofxScrollingText::getSpeed(){
    return speed;
}

ofEvent <void> ofxScrollingText::completeEvent;



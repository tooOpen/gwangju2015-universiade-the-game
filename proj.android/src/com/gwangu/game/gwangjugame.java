/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.gwangu.game;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

public class gwangjugame extends Cocos2dxActivity{
	static Handler b_handler;
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		
		final AlertDialog.Builder dia = new AlertDialog.Builder(this);
        dia.setTitle("EXIT DIALOG");   //인데 없어도 된다
        dia.setMessage("Do you want to end the game?");
        dia.setCancelable(false);
        dia.setPositiveButton("YES", new OnClickListener() {
         @Override
         public void onClick(DialogInterface dialog, int which) {
        	exitGame();
         }
        });

        dia.setNegativeButton("NO", new OnClickListener() {
         @Override
         public void onClick(DialogInterface dialog, int which) {
        
         }
        });    

        
		  b_handler = new Handler() {
				public void handleMessage(Message msg) {
					switch (msg.what) {
					case 1:
						  dia.show(); 
						break;
					}
				}
			};
	}

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// gwangjugame should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }
  

    public static void callDialog() {
		 b_handler.sendEmptyMessage(1);
		 
	}
    static {
        System.loadLibrary("cocos2dcpp");
    }
    private native void exitGame();
}

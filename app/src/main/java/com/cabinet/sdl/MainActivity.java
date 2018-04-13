package com.cabinet.sdl;

import android.content.Intent;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import org.libsdl.app.SDLActivity;

import java.io.File;


public class MainActivity extends AppCompatActivity {


    static {
        System.loadLibrary("SDL2");
        System.loadLibrary("SDL2Main");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.e("MainActivity", Environment.getExternalStorageDirectory().getPath());

        File file = new File("/storage/emulated/0/176x144______1.yuv");
        Log.e("MainActivity", file.exists()+"");
    }

    public void toSdl(View view){
        startActivity(new Intent(this, SDLActivity.class));
    }
}

package com.demo.ndkdemo;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.Button;

import com.demo.ffmpeglib.FFmpegKit;

public class FFmpegVideoPlayActivity extends AppCompatActivity {

    Button btnPlay;
    SurfaceView surfaceView;
    SurfaceHolder surfaceHolder;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ffmpeg_video_play);

        btnPlay = findViewById(R.id.btnPlay);
        btnPlay.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String path = Environment.getExternalStorageDirectory() + "/001.mp4";
                playVideo(path);
            }
        });

        surfaceView = findViewById(R.id.sfvVideo);
        surfaceHolder = surfaceView.getHolder();
    }

    private void playVideo(String path){
        FFmpegKit fFmpegKit = new FFmpegKit();
        fFmpegKit.playVideo(path, surfaceHolder.getSurface());
    }
}

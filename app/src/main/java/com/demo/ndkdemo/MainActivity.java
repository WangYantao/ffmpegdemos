package com.demo.ndkdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.demo.ffmpeglib.FFmpegKit;
import com.demo.oboelib.OboeKit;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        FFmpegKit fFmpegKit = new FFmpegKit();
        OboeKit oboeKit = new OboeKit();

        TextView txvOboe = findViewById(R.id.txvOboe);
        txvOboe.setText("oboe-info:" + oboeKit.getOboeName());

        TextView txvFFmpeg = findViewById(R.id.txvFFmpeg);
        txvFFmpeg.setText("ffmpeg-info:" + fFmpegKit.getFFmpegName());
    }
}

package com.demo.ndkdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.demo.ffmpeglib.FFmpegKit;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        FFmpegKit fFmpegKit = new FFmpegKit();

        TextView txvName = findViewById(R.id.txvName);
        txvName.setText(fFmpegKit.getFFmpegName());
    }
}

package com.demo.ndkdemo;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private final String TAG = this.getClass().getSimpleName();

    Button btnOboe, btnFFmpegPlayVideo;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnOboe = findViewById(R.id.btnOboe);
        btnOboe.setOnClickListener(this);

        btnFFmpegPlayVideo = findViewById(R.id.btnFFmpegPlayVideo);
        btnFFmpegPlayVideo.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.btnOboe:
                toNextActivity(OboeActivity.class);
                break;
            case R.id.btnFFmpegPlayVideo:
                toNextActivity(FFmpegVideoPlayActivity.class);
                break;
        }
    }

    private void toNextActivity(Class clz){
        startActivity(new Intent(MainActivity.this, clz));
    }
}

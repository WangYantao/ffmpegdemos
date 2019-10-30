package com.demo.ndkdemo;

import android.Manifest;
import android.content.pm.PackageManager;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextView;

import com.demo.oboelib.OboeKit;

import static android.support.v4.content.PermissionChecker.PERMISSION_GRANTED;

public class MainActivity extends AppCompatActivity {
    private static final int PER_REQUEST = 0;
    private static final String TAG = "mainactivity";

    OboeKit oboeKit;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        oboeKit = new OboeKit();

        View recordButton = findViewById(R.id.button_record);
        recordButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                switch(motionEvent.getAction()){
                    case MotionEvent.ACTION_DOWN:
                        oboeKit.setRecording(true);
                        break;
                    case MotionEvent.ACTION_UP:
                        oboeKit.setRecording(false);
                        break;
                }
                return true;
            }
        });

        View playButton = findViewById(R.id.button_play);
        playButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                switch(motionEvent.getAction()){
                    case MotionEvent.ACTION_DOWN:
                        oboeKit.setPlaying(true);
                        break;
                    case MotionEvent.ACTION_UP:
                        oboeKit.setPlaying(false);
                        break;
                }
                return true;
            }
        });

        Switch loopButton = findViewById(R.id.switch_loop);
        loopButton.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                oboeKit.setLooping(b);
            }
        });
    }

    @Override
    public void onResume(){
        // Check we have the record permission
        if (isRecordPermissionGranted()){
            oboeKit.startEngine();
        } else {
            Log.d(TAG, "Requesting recording permission");
            requestRecordPermission();
        }
        super.onResume();
    }

    @Override
    public void onPause() {
        oboeKit.stopEngine();
        super.onPause();
    }

    @Override
    public void onRequestPermissionsResult(int requestCode,
                                           @NonNull String permissions[],
                                           @NonNull int[] grantResults) {
        // Check that our permission was granted
        if (permissions.length > 0 &&
                permissions[0].equals(Manifest.permission.RECORD_AUDIO) &&
                grantResults[0] == PERMISSION_GRANTED) {
            oboeKit.startEngine();
        }
    }

    private void requestRecordPermission(){
        ActivityCompat.requestPermissions(
                this,
                new String[]{Manifest.permission.RECORD_AUDIO},
                PER_REQUEST);
    }

    private boolean isRecordPermissionGranted() {
        return (ActivityCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO) ==
                PackageManager.PERMISSION_GRANTED);
    }
}

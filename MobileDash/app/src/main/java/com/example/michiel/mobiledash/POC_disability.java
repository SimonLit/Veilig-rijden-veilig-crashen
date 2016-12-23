package com.example.michiel.mobiledash;

import android.app.Activity;
import android.app.KeyguardManager;
import android.content.Context;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;


public class POC_disability extends AppCompatActivity {

    boolean  disableEveryting;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_poc_disability);
        disableEveryting = false;
    }

    @SuppressWarnings("deprecation")
    private void disableKeyguard() {
        KeyguardManager mKM = (KeyguardManager) getSystemService(KEYGUARD_SERVICE);
        KeyguardManager.KeyguardLock mKL = mKM.newKeyguardLock("IN");
        mKL.disableKeyguard();
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event)

    {
        Context DisabilityContext = getBaseContext();
        if (disableEveryting)
        {
            disableKeyguard();
                switch (keyCode) {

                    case KeyEvent.KEYCODE_BACK:
                        Toast.makeText(DisabilityContext, "You pressed back, but its disabled", Toast.LENGTH_SHORT).show();
                        break;

                    case KeyEvent.KEYCODE_HOME:
                        Toast.makeText(DisabilityContext, "You pressed home, but its disabled", Toast.LENGTH_SHORT).show();
                        break;

                    case KeyEvent.KEYCODE_VOLUME_UP:
                        Toast.makeText(DisabilityContext, "You pressed volume up, but its disabled", Toast.LENGTH_SHORT).show();
                        break;

                    case KeyEvent.KEYCODE_VOLUME_DOWN:
                        Toast.makeText(DisabilityContext, "You pressed volume down, but its disabled", Toast.LENGTH_SHORT).show();
                        break;

                    case KeyEvent.KEYCODE_SLEEP:
                        Toast.makeText(DisabilityContext, "???, but its disabled", Toast.LENGTH_SHORT).show();
                        break;

                    case KeyEvent.KEYCODE_NOTIFICATION:
                        Toast.makeText(DisabilityContext, "A notification came in, but its disabled", Toast.LENGTH_SHORT).show();
                        break;

                }
            return true;
        }
        else
        {
            Toast.makeText(DisabilityContext, "You pressed something", Toast.LENGTH_SHORT).show();
            return super.onKeyDown(keyCode, event);
        }
    }

    public void DisableButtonClicked(View v)
    {
        disableEveryting = true;
    }

    public void EnableButtonClicked(View v)
    {
        disableEveryting = false;
    }
}

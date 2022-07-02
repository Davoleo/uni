package net.davoleo.memorandum.ui;

import android.location.Address;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import net.davoleo.memorandum.R;
import net.davoleo.memorandum.util.Utils;

import java.io.IOException;
import java.util.List;

public class MemoAddActivity extends AppCompatActivity {

    private static final String TAG = "MemoAddActivity";

    private Address memoLocation;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_memo_add);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        EditText locTextBox = findViewById(R.id.txb_location);

        findViewById(R.id.button_geocode).setOnClickListener(view -> {
            boolean error = false;

            try
            {
                List<Address> addresses = Utils.geocoder.getFromLocationName(locTextBox.getText().toString(),1);
                if (addresses.isEmpty())
                    error = true;
                else {
                    Address address = addresses.get(0);
                    Log.d(TAG, "button_geocode.OnClickListener: Geocoded location:\n" + address.getFeatureName() + "\n" + address.getThoroughfare() + "\n" + address.getSubThoroughfare() + "\n" + address.getLocality());
                    String locationString = String.format("%s %s %s %s",
                            address.getFeatureName() != null ? address.getFeatureName() : "",
                            address.getThoroughfare() != null ? address.getThoroughfare() : "",
                            address.getSubThoroughfare() != null ? address.getSubThoroughfare() : "",
                            address.getLocality() != null ? address.getLocality() : ""
                    ).trim();

                    if (!locationString.isEmpty())
                        locTextBox.setText(locationString);
                    else
                        error = true;
                }
            }
            catch (IOException e)
            {
                Log.w(TAG, "button_geocode.OnClickListener: Error while geocoding position for location name: " + locTextBox.getText().toString());
            }
            finally
            {
                if (error)
                    locTextBox.setError("No Location found");
                else
                    locTextBox.setError(null);
            }
        });


    }

    public void addMemo(View view)
    {

    }
}
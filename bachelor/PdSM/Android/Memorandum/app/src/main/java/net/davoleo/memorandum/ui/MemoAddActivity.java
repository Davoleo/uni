package net.davoleo.memorandum.ui;

import android.content.Intent;
import android.location.Address;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import com.google.android.material.snackbar.Snackbar;
import com.google.android.material.textfield.TextInputLayout;
import net.davoleo.memorandum.R;
import net.davoleo.memorandum.model.Location;
import net.davoleo.memorandum.model.Memo;
import net.davoleo.memorandum.model.MemoStatus;
import net.davoleo.memorandum.util.Utils;

import java.io.IOException;
import java.util.Calendar;
import java.util.List;
import java.util.Locale;

public class MemoAddActivity extends AppCompatActivity {

    private static final String TAG = "MemoAddActivity";

    private static final int ERR_OK = 0;
    private static final int ERR_NO_RESULTS = 1;
    private static final int ERR_IO = 2;

    @Nullable
    private Address memoLocation;
    @Nullable
    private Calendar memoTimestamp;

    private ImageButton geocodeButton;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_memo_add);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        Button dateTimeButton = findViewById(R.id.button_timestamp);
        dateTimeButton.setOnClickListener(view -> {
            Utils.showDateTimePickerDialog(this, (year, month, day, hour, minute) -> {
                dateTimeButton.setText(String.format(
                        Locale.getDefault(),
                        "%02d/%02d/%d - %02d:%02d",
                        day, month, year, hour, minute
                ));
                if (memoTimestamp == null)
                    memoTimestamp = Calendar.getInstance();
                memoTimestamp.set(year, month, day, hour, minute);
                Log.d(TAG, String.format("datePicked: %d, %d, %d, %d, %d%n", year, month, day, hour, minute));
            });
        });

        geocodeButton = findViewById(R.id.button_geocode);
        geocodeButton.setOnClickListener(view ->
            MainActivity.memorandumExecutor.submit(() -> {
                geocodeButton.setImageResource(R.drawable.ic_sync);
                buttonGeocodeHandler(findViewById(R.id.txb_location), findViewById(R.id.txb_location_layout));
            })
        );

        findViewById(R.id.button_add).setOnClickListener(this::addMemo);
    }

    private void buttonGeocodeHandler(EditText locTextBox, TextInputLayout locTextInputLayout) {
        int error = ERR_OK;

        try
        {
            List<Address> addresses = Utils.getGeocoder(this).getFromLocationName(locTextBox.getText().toString(),1);
            if (addresses.isEmpty())
                error = ERR_NO_RESULTS;
            else {
                Address address = addresses.get(0);
                Log.d(TAG, "button_geocode.OnClickListener: Geocoded location:\n" + address.getFeatureName() + "\n" + address.getThoroughfare() + "\n" + address.getSubThoroughfare() + "\n" + address.getLocality());


                String featureString = "";
                if (!address.getFeatureName().equals(address.getThoroughfare()) &&
                        !address.getFeatureName().equals(address.getSubThoroughfare()) &&
                        !address.getFeatureName().equals(address.getLocality()))
                    featureString = address.getFeatureName() != null ? address.getFeatureName() : "";

                String locationString = String.format("%s %s %s %s",
                        featureString,
                        address.getThoroughfare() != null ? address.getThoroughfare() : "",
                        address.getSubThoroughfare() != null ? address.getSubThoroughfare() : "",
                        address.getLocality() != null ? address.getLocality() : ""
                ).trim();

                if (!locationString.isEmpty()) {
                    memoLocation = address;
                    Utils.MAIN_UI_THREAD_HANDLER.post(() -> {
                        locTextBox.setText(locationString);
                        geocodeButton.setImageResource(R.drawable.ic_my_location);
                    });
                }
                else
                    error = ERR_NO_RESULTS;
            }
        }
        catch (IOException e)
        {
            error = ERR_IO;
            Log.w(TAG, "button_geocode.OnClickListener: Error while geocoding position for location name: " + locTextBox.getText().toString());
            e.printStackTrace();
        }
        finally
        {
            int finalError = error;
            Utils.MAIN_UI_THREAD_HANDLER.post(() -> {
                switch (finalError) {
                    case ERR_IO:
                        memoLocation = null;
                        locTextInputLayout.setError("Connection Error");
                        geocodeButton.setImageResource(R.drawable.ic_location_searching);
                    case ERR_NO_RESULTS:
                        memoLocation = null;
                        locTextInputLayout.setError("No Location found!");
                        geocodeButton.setImageResource(R.drawable.ic_location_searching);
                        break;
                    case ERR_OK:
                        locTextInputLayout.setError(null);
                        break;
                }
            });
        }
    }

    public void addMemo(View view)
    {
        TextInputLayout titleBoxLayout = findViewById(R.id.txb_title_layout);
        EditText titleBox = findViewById(R.id.txb_title);

        if (titleBox.getText().toString().isEmpty()) {
            titleBoxLayout.setError("The title is Required!");
            return;
        }
        else
            titleBoxLayout.setError(null);


        if (memoTimestamp == null) {
            Snackbar.make(view, "You need to set Date/Time for this memo before adding it!", Snackbar.LENGTH_LONG).show();
            return;
        }

        if (memoLocation == null) {
            Snackbar.make(view, "You need to set a location for this memo before adding it!", Snackbar.LENGTH_LONG).show();
            return;
        }

        EditText descBox = findViewById(R.id.txb_desc);

        Memo memo = new Memo(
                titleBox.getText().toString(),
                descBox.getText().toString(),
                MemoStatus.ACTIVE,
                memoTimestamp.getTime(),
                new Location(memoLocation.getLongitude(), memoLocation.getLatitude())
        );

        Intent intent = new Intent();
        intent.putExtras(memo.toBundle());
        setResult(RESULT_OK, intent);
        this.finish();
    }
}
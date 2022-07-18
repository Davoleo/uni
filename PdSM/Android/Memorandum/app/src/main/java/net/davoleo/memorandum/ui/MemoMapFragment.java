package net.davoleo.memorandum.ui;

import android.content.SharedPreferences;
import android.graphics.Color;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ProgressBar;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.preference.PreferenceManager;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.CircleOptions;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;
import net.davoleo.memorandum.R;
import net.davoleo.memorandum.model.Memo;
import net.davoleo.memorandum.model.MemoStatus;
import net.davoleo.memorandum.persistence.MemorandumDatabase;
import net.davoleo.memorandum.util.Utils;

import java.util.List;

public class MemoMapFragment extends Fragment implements OnMapReadyCallback {

    private ProgressBar activityProgressIndicator;

    private List<Memo> mapMemos;

    /**
     * Manipulates the map once available.
     * This callback is triggered when the map is ready to be used.
     * This is where we can add markers or lines, add listeners or move the camera.
     * In this case, we just add a marker near Sydney, Australia.
     * If Google Play services is not installed on the device, the user will be prompted to
     * install it inside the SupportMapFragment. This method will only be triggered once the
     * user has installed Google Play services and returned to the app.
     */
    @Override
    public void onMapReady(GoogleMap googleMap)
    {
        //Should be always nonnull
        activityProgressIndicator.setVisibility(View.GONE);

        LatLng firstLocation = null;

        for (Memo memo : mapMemos)
        {
            LatLng location = new LatLng(memo.getLocation().getLatitude(), memo.getLocation().getLongitude());

            if (firstLocation == null)
                firstLocation = location;

            MarkerOptions marker = new MarkerOptions()
                    .position(location)
                    .title(memo.title)
                    .snippet(memo.description);
            googleMap.addMarker(marker);


            SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(getContext());
            CircleOptions circle = new CircleOptions()
                    .center(location)
                    .radius(prefs.getInt("location_radius", 200))
                    .strokeWidth(4)
                    .strokeColor(Color.argb(255, 255, 0, 0))
                    .fillColor(Color.argb(64, 255, 0, 0));
            googleMap.addCircle(circle);
        }

        if (firstLocation != null)
            googleMap.moveCamera(CameraUpdateFactory.newLatLngZoom(firstLocation, 10));
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState)
    {
        return inflater.inflate(R.layout.fragment_memo_map, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState)
    {
        super.onViewCreated(view, savedInstanceState);
        SupportMapFragment mapFragment = (SupportMapFragment) getChildFragmentManager().findFragmentById(R.id.map);

        if (getActivity() instanceof MainActivity)
            activityProgressIndicator = ((MainActivity) getActivity()).progressIndicator;

        assert activityProgressIndicator != null;
        activityProgressIndicator.setVisibility(View.VISIBLE);

        MainActivity.memorandumExecutor.submit(() -> {
            mapMemos = MemorandumDatabase.instance.memoDAO().getAllOfStatusSorted(MemoStatus.ACTIVE);

            Utils.MAIN_UI_THREAD_HANDLER.post(() -> {
                if (mapFragment != null)
                    mapFragment.getMapAsync(this);
            });
        });

    }
}
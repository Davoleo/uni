package net.davoleo.memorandum.ui;

import android.os.Bundle;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;
import com.google.android.material.tabs.TabLayout;
import androidx.viewpager.widget.ViewPager;
import androidx.appcompat.app.AppCompatActivity;
import net.davoleo.memorandum.R;
import net.davoleo.memorandum.model.Memo;
import net.davoleo.memorandum.persistence.MemorandumDatabase;
import net.davoleo.memorandum.ui.main.SectionsPagerAdapter;

import java.util.List;

public class MainActivity extends AppCompatActivity {

    private ViewPager viewPager;

    protected List<Memo> memos;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        MemorandumDatabase.init(this);

        setContentView(R.layout.activity_main);

        viewPager = findViewById(R.id.view_pager);

        SectionsPagerAdapter sectionsPagerAdapter = new SectionsPagerAdapter(getSupportFragmentManager(), this);
        viewPager.setAdapter(sectionsPagerAdapter);
        TabLayout tabs = findViewById(R.id.tabs);
        tabs.setupWithViewPager(viewPager);

        FloatingActionButton fab = findViewById(R.id.fab);
        fab.setOnClickListener(view -> Snackbar.make(view, "NYI (add new )", Snackbar.LENGTH_LONG)
                .setAction("Action", null).show());
    }
}
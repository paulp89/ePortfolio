package com.pathana.inventory_app;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class MainActivity extends AppCompatActivity {


    private EditText logName, logPass;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        logName = findViewById(R.id.logName);
        logPass = findViewById(R.id.logPass);


    }

    /**
     * If the data provided is valid, logs the user in
     * and changes activity
     */
    public void logIn(View view){
        if (emptyInputs()) return;
        //ask for database
        Database db = new Database(MainActivity.this);
        boolean result = db.checkUser(logName.getText().toString(), logPass.getText().toString());
        if (result){
            Intent intent = new Intent(this, InventoryActivity.class);
            startActivity(intent);
        } else {
            Toast.makeText(MainActivity.this,  "Invalid username or password",Toast.LENGTH_SHORT).show();
        }
    }

    /**
     * If the data provided is valid,
     * adds the new user to the database.
     */
    public void signUp(View view){
        if (emptyInputs()) return;
        try( Database db = new Database(MainActivity.this);) {
            boolean result = db.addUser(logName.getText().toString(), logPass.getText().toString());
            if (result){
                Toast.makeText(MainActivity.this,  "Success!",Toast.LENGTH_SHORT).show();
                logName.getText().clear();
                logPass.getText().clear();
            } else {
                Toast.makeText(MainActivity.this,  "Name already taken",Toast.LENGTH_SHORT).show();
            }
        }
    }

    /**
     *
     * @return true if there is an empty input field
     */
    private boolean emptyInputs(){
        if (logName.getText().toString().trim().isEmpty()){
            //Toast.makeText(MainActivity.this,  "User cannot be empty",Toast.LENGTH_SHORT).show();
            logName.setError("User cannot be empty");
            return true;
        } else if (logPass.getText().toString().trim().isEmpty()){
            logPass.setError("Password cannot be empty");
            return true;
        }
        return false;
    }

    @Override
    protected void onStop() {
        super.onStop();
        logName.getText().clear();
        logPass.getText().clear();
    }
}
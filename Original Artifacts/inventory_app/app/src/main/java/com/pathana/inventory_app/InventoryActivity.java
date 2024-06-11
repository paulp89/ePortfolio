package com.pathana.inventory_app;


import android.Manifest;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;
import android.widget.Toast;

import java.util.List;
import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;


public class InventoryActivity extends AppCompatActivity {
    
    private TableLayout listGrid;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_inventory);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        listGrid = findViewById(R.id.listGrid);
        loadData();
        checkPermissions();
    }


    /**
     * Fills the TableLayout with data from the database
     */
    public void loadData(){
        try ( Database db = new Database(InventoryActivity.this);) {
            List<Shoe> shoes = db.getShoes();
            listGrid.removeAllViews();
            if (shoes.isEmpty()) {
                TextView txt = new TextView(InventoryActivity.this);
                txt.setText("No shoes in inventory.");
                txt.setGravity(Gravity.CENTER);
                listGrid.addView(txt);
            } else {
                for (Shoe shoe : shoes) {
                    listGrid.addView(getDisplayView(shoe));
                }
            }
        }
    }

    /**
     * Triggers dialog to add a new shoe
     */
    public void newShoe(View view){
        ShoeDialog dialog = new ShoeDialog();
        dialog.show(getSupportFragmentManager(), "New Shoe");
    }


    /**
     *
     * This function is used to populate the TableLayout object
     * that I'm using to display information to the user.
     *
     * Each object has its own buttons to edit and delete itself.
     *
     * @param shoe shoe object to represent as a TableRow object
     * @return a TableRow object that can be displayed to the user
     */
    private TableRow getDisplayView(Shoe shoe){
        LayoutInflater inflater = getLayoutInflater();
        TableRow row = new TableRow(InventoryActivity.this);
        View layout = inflater.inflate(R.layout.shoe_table_row, null,false);

        ((TextView) layout.findViewById(R.id.labelID) ).setText(String.format("ID #%d", shoe.getID()));
        ((TextView) layout.findViewById(R.id.labelBrand) ).setText(shoe.getBrand());
        ((TextView) layout.findViewById(R.id.labelModel) ).setText(shoe.getModel());
        ((TextView) layout.findViewById(R.id.labelPrice) ).setText(String.format("$%.2f", shoe.getPrice()));
        ((TextView) layout.findViewById(R.id.labelSize) ).setText(String.format("%.2f", shoe.getSize()));

        TextView labelStock = layout.findViewById(R.id.labelStock);
        labelStock.setText(String.format("%d", shoe.getStock()));
        if (shoe.getStock() == 0){
            labelStock.setTextColor(Color.parseColor("#D83B3B"));
            labelStock.setText("OUT OF STOCK");
        }

        Button delete = layout.findViewById(R.id.btnDelete);
        Button edit = layout.findViewById(R.id.btnStock);

        delete.setOnClickListener(view -> {
            deleteShoe(shoe.getID());
        });

        edit.setOnClickListener( view ->{
            updateShoe(shoe);
        });

        row.addView(layout);
        return row;
    }

    /**
     *
     * Deletes a shoe and updates view
     * @param ID of the shoe to delete
     */
    private void deleteShoe(int ID){
        try (Database db = new Database(InventoryActivity.this)) {
            if (!db.removeShoe(ID)) {
                Toast.makeText(InventoryActivity.this, "Database error", Toast.LENGTH_SHORT).show();
            } else {
                loadData();
            }
        }
    }

    /**
     *
     * Shows a dialog to update a selected shoe
     *
     * @param shoe to update
     */
    private void updateShoe(Shoe shoe){
        ShoeDialog dialog = new ShoeDialog();
        dialog.setToUpdate(shoe);
        dialog.show(getSupportFragmentManager(), "Update Shoe");
    }

    @Override
    protected void onStop() {
        super.onStop();
        notifyLowStock();
    }

    /**
     * If there is a low stock item, sends a notification
     */
    private void notifyLowStock(){
        try (Database db = new Database(InventoryActivity.this)) {
            if (db.hasLowStock(0)) {
                sendSMS();
            }
        }
    }

    /**
     * Sends SMS notification
     */
    private void sendSMS(){
        String PERMISSION = Manifest.permission.SEND_SMS;
        if (ActivityCompat.checkSelfPermission(this, PERMISSION) == PackageManager.PERMISSION_GRANTED){
            SmsManager smsManager = SmsManager.getDefault();
            smsManager.sendTextMessage("+1-555-521-5554", null, "Some items are on low stock!", null, null);
            Intent sendIntent = new Intent(Intent.ACTION_VIEW);

            sendIntent.putExtra("sms_body", "default content");
            sendIntent.setType("vnd.android-dir/mms-sms");
            try {
                startActivity(sendIntent);
            } catch (ActivityNotFoundException ignored){

            }
        }
    }


    /**
     * Checks for SMS permissions
     */
    private void checkPermissions(){
        String PERMISSION = Manifest.permission.SEND_SMS;
        if (ActivityCompat.checkSelfPermission(this, PERMISSION) != PackageManager.PERMISSION_GRANTED) {
            if (ActivityCompat.shouldShowRequestPermissionRationale(this, PERMISSION)){
                AlertDialog.Builder builder = new AlertDialog.Builder(this);
                builder.setMessage("This app requires permission to send you SMS notifications.")
                        .setTitle("Permission Request")
                        .setCancelable(false)
                        .setPositiveButton("Ok", (dialogInterface, i) -> {
                            ActivityCompat.requestPermissions(this, new String[]{PERMISSION}, 1234);
                            dialogInterface.dismiss();
                        })
                        .setNegativeButton("Cancel", (dialogInterface, i) -> {
                            dialogInterface.dismiss();
                        });
                builder.show();
            } else {
                ActivityCompat.requestPermissions(this, new String[]{PERMISSION}, 1234);
            }
        }
    }


}
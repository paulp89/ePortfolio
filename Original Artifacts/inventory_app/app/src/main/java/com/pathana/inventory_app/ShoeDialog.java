package com.pathana.inventory_app;

import android.app.AlertDialog;
import android.app.Dialog;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.DialogFragment;

/**
 * Dialog for inserting/updating a shoe in the database
 */
public class ShoeDialog  extends DialogFragment {


    private EditText brand, model, price, size, stock;
    private Shoe shoeToUpdate = null;

    @NonNull
    @Override
    public Dialog onCreateDialog(@Nullable Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        // Get the layout inflater.
        LayoutInflater inflater = requireActivity().getLayoutInflater();

        // Inflate and set the layout for the dialog.
        // Pass null as the parent view because it's going in the dialog layout.
        builder.setView(inflater.inflate(R.layout.add_shoe_input_form, null))
                // Add action buttons
                .setPositiveButton("Save", (dialogInterface, i) -> {

                })
                .setNegativeButton("Cancel", (dialog, id) -> {
                    //ShoeDialog.this.getDialog().cancel();
                });

        return builder.create();
    }


    @Override
    public void onStart() {
        super.onStart();
        //get references to the text input fields
        brand = this.getDialog().findViewById(R.id.txtShoeBrand);
        model = this.getDialog().findViewById(R.id.txtShoeModel);
        price = this.getDialog().findViewById(R.id.txtShoePrice);
        size = this.getDialog().findViewById(R.id.txtShoeSize);
        stock = this.getDialog().findViewById(R.id.txtShoeStock);

        //if we have an object to update, fill text fields with shoe data
        if (shoeToUpdate != null){
            brand.setText(shoeToUpdate.getBrand());
            model.setText(shoeToUpdate.getModel());
            price.setText(String.valueOf(shoeToUpdate.getPrice()));
            size.setText(String.valueOf(shoeToUpdate.getSize()));
            stock.setText(String.valueOf(shoeToUpdate.getStock()));
        }

        //save button
        Button btn  = ((AlertDialog) getDialog()).getButton(AlertDialog.BUTTON_POSITIVE);
        btn.setOnClickListener(view -> saveShoe());

        size.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {

            }

            //No negative sizes on my watch!
            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                if (size.getText().toString().contains("-")) size.getText().clear();
            }

            @Override
            public void afterTextChanged(Editable editable) {

            }
        });
    }

    private void saveShoe(){
        if (inputSanitized()){
            //get data from text fields
            String shoeBrand = brand.getText().toString().trim();
            String shoeModel = model.getText().toString().trim();
            double shoePrice = Double.parseDouble(price.getText().toString());
            double shoeSize = Double.parseDouble(size.getText().toString());
            int shoeStock = Integer.parseInt(stock.getText().toString());
            //create Shoe object
            Shoe shoe = new Shoe(0, shoeBrand, shoeModel, shoePrice, shoeSize, shoeStock);

            //Reference to the database
            Database db = new Database(getActivity());
            boolean success;

            //insert Shoe into the database
            if (shoeToUpdate == null){
                success = db.addShoe(shoe);
            } else {
                //update shoe
                success = db.updateShoe(shoe, shoeToUpdate.getID());
            }

            if (success){
                InventoryActivity activity = (InventoryActivity) getContext();
                activity.loadData();
                dismiss();
            } else {
                Toast.makeText(getContext(), "Update unsuccessful", Toast.LENGTH_SHORT).show();
            }
        }
    }

    /**
     * @return true if all the input fields have valid data
     */
    private boolean inputSanitized(){
        boolean output = checkTextInput(brand, "Brand cannot be empty");
        output &= checkTextInput(model, "Model cannot be empty");
        output &= checkTextInput(price, "Price is required");
        output &= checkTextInput(size, "Size is required");
        output &= checkTextInput(stock, "Stock is required");
        return output;
    }

    /**
     *
     * Checks whether a input field is empty
     *
     * @param field to check
     * @param msg error message
     * @return empty status
     */
    private boolean checkTextInput(EditText field, String msg){
        if (field.getText().toString().trim().isEmpty()){
            field.setError(msg);
            return false;
        }
        return true;
    }

    /**
     * @param shoe reference to update
     */
    public void setToUpdate(Shoe shoe){
        shoeToUpdate = shoe;
    }

}

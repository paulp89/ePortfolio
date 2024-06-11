package com.pathana.inventory_app;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import java.util.ArrayList;
import java.util.List;

import androidx.annotation.Nullable;


public class Database extends SQLiteOpenHelper {
    public static final String TABLE_USERS = "USERS";
    public static final String COL_NAME = "NAME";
    public static final String COL_PASS = "PASS";
    public static final String TABLE_SHOES = "SHOES";
    public static final String COL_BRAND = "BRAND";
    public static final String COL_MODEL = "MODEL";
    public static final String COL_PRICE = "PRICE";
    public static final String COL_SIZE = "SIZE";
    public static final String COL_STOCK = "STOCK";


    public Database(@Nullable Context context) {
        super(context, "data.db", null, 1);
    }

    //init method
    @Override
    public void onCreate(SQLiteDatabase db) {
        String userTableSource = "CREATE TABLE " + TABLE_USERS + "(" + COL_NAME + " TEXT PRIMARY KEY, " + COL_PASS + " TEXT)";

        String shoeTableSource = "CREATE TABLE " + TABLE_SHOES + "(" +
                "ID INTEGER PRIMARY KEY AUTOINCREMENT," +
                COL_BRAND + " TEXT," +
                " " + COL_MODEL + " TEXT,  " +
                COL_PRICE + " REAL, " +
                COL_SIZE + " REAL,  " +
                COL_STOCK + " INTEGER)";

        db.execSQL(userTableSource);
        db.execSQL(shoeTableSource);
    }

    //compatibility
    @Override
    public void onUpgrade(SQLiteDatabase db, int i, int i1) {

    }

    /**
     *
     * Inserts a new user into the database
     *
     * @param name of the user
     * @param pass user password
     * @return whether or not the operation was sucessful
     */
    public boolean addUser(String name, String pass){
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues cv = new ContentValues();
        cv.put(COL_NAME, name);
        cv.put(COL_PASS, pass);
        return db.insert(TABLE_USERS, null, cv) > 0;
    }

    /**
     *
     *
     * Checks whether a given username + password pair exists in the databse
     * @param name  name to check
     * @param pass password to check
     * @return answer
     */
    public boolean checkUser(String name, String pass){
        SQLiteDatabase db = this.getReadableDatabase();
        String query = "SELECT 1 FROM "+TABLE_USERS+" WHERE "+COL_NAME+" = ? AND "+COL_PASS+" = ? LIMIT 1";
        Cursor cursor = db.rawQuery(query, new String[]{name, pass});
        boolean output = cursor.moveToFirst();
        cursor.close();
        db.close();
        return output;
    }

    /**
     *
     *Inserts a shoe into the database
     *
     * @param shoe object with data
     * @return success or failure of the SQL operation
     */
    public boolean addShoe(Shoe shoe){
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues cv = new ContentValues();
        cv.put(COL_BRAND, shoe.getBrand());
        cv.put(COL_MODEL, shoe.getModel());
        cv.put(COL_PRICE, shoe.getPrice());
        cv.put(COL_SIZE, shoe.getSize());
        cv.put(COL_STOCK, shoe.getStock());
        return db.insert(TABLE_SHOES, null, cv) > 0;
    }

    /**
     *
     * Updates a record in the shoe table
     *
     * @param shoe an object with updated data but ID 0
     * @param ID  correct id to update in the database
     * @return success of the SQL operation
     */
    public boolean updateShoe(Shoe shoe, int ID){
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues cv = new ContentValues();
        cv.put(COL_BRAND, shoe.getBrand());
        cv.put(COL_MODEL, shoe.getModel());
        cv.put(COL_PRICE, shoe.getPrice());
        cv.put(COL_SIZE, shoe.getSize());
        cv.put(COL_STOCK, shoe.getStock());
        int output = 0;
        try {
            output = db.update(TABLE_SHOES, cv,"ID = ?", new String[]{String.valueOf(ID)});
        } catch (Exception e){
            System.err.print(e.getMessage());
        }
        return output > 0;
    }

    /**
     *
     * Deletes a shoe from the database
     *
     * @param ID  shoe to eliminate
     * @return whether or not the operation was successful
     */
    public boolean removeShoe(int ID){
        SQLiteDatabase db = this.getWritableDatabase();
        return  0 < db.delete(TABLE_SHOES, "ID = ?", new String[]{String.valueOf(ID)});
    }

    /**
     * @return a list of Shoe objects stored in the database
     */
    public List<Shoe> getShoes(){
        List<Shoe> outputShoes = new ArrayList<>();
        String query = "SELECT * FROM "+TABLE_SHOES;
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.rawQuery(query, null);

        if (cursor.moveToFirst()){
            do {
                int id = cursor.getInt(0);
                String brand = cursor.getString(1);
                String model = cursor.getString(2);
                double price = cursor.getDouble(3);
                double size = cursor.getDouble(4);
                int stock = cursor.getInt(5);
                Shoe shoe = new Shoe(id, brand, model, price, size, stock);
                outputShoes.add(shoe);
            } while (cursor.moveToNext());
        }
        cursor.close();
        db.close();
        return outputShoes;
    }

    /**
     * @param low lowest stock to check for
     * @return true if there is a record with low stock
     */
    public boolean hasLowStock(int low){
        SQLiteDatabase db = this.getReadableDatabase();
        String query = "SELECT 1 FROM "+TABLE_SHOES+" WHERE "+COL_STOCK+" <= ?  LIMIT 1";
        Cursor cursor = db.rawQuery(query, new String[]{String.valueOf(low)});
        boolean output = cursor.moveToFirst();
        cursor.close();
        db.close();
        return output;
    }



}

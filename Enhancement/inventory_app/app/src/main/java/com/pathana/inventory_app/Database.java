package com.pathana.inventory_app;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

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
    public static final String COL_IMG = "IMAGE";

    public Database(@Nullable Context context) {
        super(context, "data.db", null, 1);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        try {
            String userTableSource = "CREATE TABLE " + TABLE_USERS + "(" + COL_NAME + " TEXT PRIMARY KEY, " + COL_PASS + " TEXT)";
            String shoeTableSource = "CREATE TABLE " + TABLE_SHOES + "(" +
                    "ID INTEGER PRIMARY KEY AUTOINCREMENT," +
                    COL_BRAND + " TEXT," +
                    COL_MODEL + " TEXT, " +
                    COL_PRICE + " REAL, " +
                    COL_SIZE + " REAL, " +
                    COL_STOCK + " INTEGER, " +
                    COL_IMG + " TEXT)";
            db.execSQL(userTableSource);
            db.execSQL(shoeTableSource);
            Log.d("Database", "Tables created successfully");
        } catch (Exception e) {
            Log.e("Database", "Error creating tables: " + e.getMessage());
        }
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // Handle database upgrade as needed
    }

    public boolean addUser(String name, String pass) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues cv = new ContentValues();
        cv.put(COL_NAME, name);
        cv.put(COL_PASS, pass);
        long result = db.insert(TABLE_USERS, null, cv);
        db.close();
        return result > 0;
    }

    public boolean checkUser(String name, String pass) {
        SQLiteDatabase db = this.getReadableDatabase();
        String query = "SELECT 1 FROM " + TABLE_USERS + " WHERE " + COL_NAME + " = ? AND " + COL_PASS + " = ? LIMIT 1";
        Cursor cursor = db.rawQuery(query, new String[]{name, pass});
        boolean output = cursor.moveToFirst();
        cursor.close();
        db.close();
        return output;
    }

    public boolean addShoe(Shoe shoe) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues cv = new ContentValues();
        cv.put(COL_BRAND, shoe.getBrand());
        cv.put(COL_MODEL, shoe.getModel());
        cv.put(COL_PRICE, shoe.getPrice());
        cv.put(COL_SIZE, shoe.getSize());
        cv.put(COL_STOCK, shoe.getStock());
        cv.put(COL_IMG, shoe.getImage());
        long result = db.insert(TABLE_SHOES, null, cv);
        db.close();
        return result > 0;
    }

    public boolean updateShoe(Shoe shoe, int ID) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues cv = new ContentValues();
        cv.put(COL_BRAND, shoe.getBrand());
        cv.put(COL_MODEL, shoe.getModel());
        cv.put(COL_PRICE, shoe.getPrice());
        cv.put(COL_SIZE, shoe.getSize());
        cv.put(COL_STOCK, shoe.getStock());
        cv.put(COL_IMG, shoe.getImage());
        int output = 0;
        try {
            output = db.update(TABLE_SHOES, cv, "ID = ?", new String[]{String.valueOf(ID)});
        } catch (Exception e) {
            Log.e("Database", "Error updating shoe: " + e.getMessage());
        } finally {
            db.close();
        }
        return output > 0;
    }

    public boolean removeShoe(int ID) {
        SQLiteDatabase db = this.getWritableDatabase();
        int result = db.delete(TABLE_SHOES, "ID = ?", new String[]{String.valueOf(ID)});
        db.close();
        return result > 0;
    }

    public List<Shoe> getShoes() {
        List<Shoe> outputShoes = new ArrayList<>();
        String query = "SELECT * FROM " + TABLE_SHOES;
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.rawQuery(query, null);

        if (cursor.moveToFirst()) {
            do {
                int id = cursor.getInt(0);
                String brand = cursor.getString(1);
                String model = cursor.getString(2);
                double price = cursor.getDouble(3);
                double size = cursor.getDouble(4);
                int stock = cursor.getInt(5);
                String img = cursor.getString(6);
                Shoe shoe = new Shoe(id, brand, model, price, size, stock);
                shoe.setImage(img);
                outputShoes.add(shoe);
            } while (cursor.moveToNext());
        }
        cursor.close();
        db.close();
        return outputShoes;
    }

    public boolean hasLowStock(int low) {
        SQLiteDatabase db = this.getReadableDatabase();
        String query = "SELECT 1 FROM " + TABLE_SHOES + " WHERE " + COL_STOCK + " <= ? LIMIT 1";
        Cursor cursor = db.rawQuery(query, new String[]{String.valueOf(low)});
        boolean output = cursor.moveToFirst();
        cursor.close();
        db.close();
        return output;
    }
}

package com.pathana.inventory_app;

import androidx.annotation.NonNull;

/**
 * Shoe model
 */
public class Shoe {
    /**
     * unique ID for database purposes
     */
    private final int ID;
    private int stock;
    private String brand, model;
    private double price, size;

    public Shoe(int ID, String brand, String name, double price, double size, int stock) {
        this.ID = ID;
        this.stock = stock;
        this.brand = brand;
        this.model = name;
        this.price = price;
        this.size = size;
    }

    /**
     *
     *
     * Getters and setters
     */
    public int getID() {
        return ID;
    }

    public int getStock() {
        return stock;
    }

    public void setStock(int stock) {
        this.stock = stock;
    }

    public String getBrand() {
        return brand;
    }

    public void setBrand(String brand) {
        this.brand = brand;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public double getSize() {
        return size;
    }

    public void setSize(double size) {
        this.size = size;
    }

    @NonNull
    @Override
    public String toString() {
        return " " + this.brand +
                " " + this.model +
                " " + this.price +
                " " + this.size +
                " " + this.stock;
    }
}

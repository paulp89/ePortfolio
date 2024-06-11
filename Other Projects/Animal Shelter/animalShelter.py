#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Feb 1 03:13:06 2024

@author: paulpathana_snhu
"""

from pymongo import MongoClient

class AnimalShelter(object):
    """ CRUD operations for Animal collection in MongoDB """

    def __init__(self, USER, PASS):
        # Initializing the MongoClient. This helps to 
        # access the MongoDB databases and collections.
        # This is hard-wired to use the aac database, the 
        # animals collection, and the aac user.
        # Definitions of the connection string variables are
        # unique to the individual Apporto environment.
        #
        # You must edit the connection variables below to reflect
        # your own instance of MongoDB!
        #
        # Connection Variables
        #
        USER = 'aacuser'
        PASS = 'SNHU1234'
        HOST = 'nv-desktop-services.apporto.com'
        PORT = 30175
        DB = 'AAC'
        COL = 'animals'
        #
        # Initialize Connection
        #
        self.client = MongoClient('mongodb://%s:%s@%s:%d' % (USER, PASS, HOST, PORT))
        self.database = self.client['%s' % (DB)]
        self.collection = self.database['%s' % (COL)]
        print("Connection Successful")
        
   
       

    # Complete this create method to implement the C in CRUD.
    def create(self, data):
        if data is not None:
            self.database.animals.insert_one(data)
            return True
    
        else:
            print("Error: Nothing to save, because data parameter is empty")
           

    # Create method to implement the R in CRUD.
    def read(self, query):
        if query:
            result = self.database.animals.find(query, {"_id": False})
        else:
            result = self.database.animals.find({}, {"_id": False})
        return result
    
    # Create this method to implement the U in CRUD
    def update(self, criteria, updateData):
        if updateData is not None:
            update_result = self.database.animals.update_many(criteria, {'$set': updateData})
            return update_result.modified_count
        else:
            raise Exception("Nothing to update, data is empty")

    # Create this method to implement the D in CRUD
    def delete(self, criteria):
        if criteria is not None:
            delete_result = self.database.animals.delete_many(criteria)
            return delete_result.deleted_count
        else:
            raise Exception("Nothing to delete, criteria is empty")

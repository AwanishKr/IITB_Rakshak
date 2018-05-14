from sklearn.metrics import accuracy_score
import pandas as pd
import numpy as np
from numpy import *
import matplotlib.pyplot as plt    
from sklearn import datasets
from sklearn import svm  					                    				
    	            		                            
df = pd.read_csv("F:\Academics\SEM-6\EE-769-Machine-Learning\Assignment\House_trainSold.csv")

#apply hot encoding on columns having mixed data 
df = pd.get_dummies(df, columns=["MasVnrArea", "GarageYrBlt"])

#for count, value in enumerate(df):
#   print count, value 

#extract objects column
obj_df = df.select_dtypes(include=['object']).copy()

# convert objects into numerical values using label encoding to avoid increase in number of columns 
# this loop is written by me
for col in obj_df:  					
    obj_df[col] = obj_df[col].astype('category')
    obj_df[col] = obj_df[col].cat.codes
#this loop is written by me 
#reconstructing df
for element in df:
       for c in obj_df:
	        if(element == c):
	            df[element] = obj_df[c]
print(df.shape)
#from dataframe to numpy array
df = df.values

#column wise normalization
df_new = df[:, 0:32]
print(df_new.shape)
df_new[:,:] = (df_new[:,:] - mean(df_new[:,:], axis = 0))/ std(df_new[:,:], axis = 0)

#X = df[:, 1:3]                         			                 	 	    		# we only take the feature columns.
#y = df[:, 0]						                   	          	    		# we only take last column as target 
#C = 1.0             	                                                               	                        # SVM regularization parameter
#create dataset_1										    		# svc.decision_function(X_1)							
#division of dataset is written by me 										# for k, value_k in enumerate(list_kernel):									
X_1 = df[:700, :32]
y_1_true = df[:700, 32]

#create dataset_2
X_2 = df[700:, :32]
y_2_true = df[700:, 32]

#this loop is written by me 
#list_gammaValue = [0.0000305, 0.0001, 0.00488, 0.00195, 0.0078, 0.03125, 0.125, 0.5, 0.7]
#list_CValue = [0.03125, 0.125, 0.5, 2, 8, 32, 128, 512, 2048]
#max_accuracy = 0
#for i, value_i in enumerate(list_gammaValue):
#    for j, value_j in enumerate(list_CValue):
#        svc = svm.SVC(kernel = 'rbf', gamma = list_gammaValue[i], C = list_CValue[j]).fit(X_1, y_1_true)
#        y_2_pred =  svc.predict(X_2)
#        if(max_accuracy < accuracy_score(y_2_true, y_2_pred)):
#            max_accuracy = accuracy_score(y_2_true, y_2_pred)    

#print("before: ", max_accuracy)
# this part is commented because it was taking very more time to run for the loops two times  
# for k, value_k in enumerate(list_gammaValue):
#    for j, value_j in enumerate(list_CValue):
#        svc = svm.SVC(kernel = 'rbf', gamma = list_gammaValue[k], C = list_CValue[j]).fit(X_1, y_1_true)
#        y_2_pred =  svc.predict(X_2)
#        if(max_accuracy == accuracy_score(y_2_true, y_2_pred)):
#            max_C = value_j
#            max_gamma = value_k

# now we have best combination for C and gamma 
print(type(df))
X = df_new[:, :32]
y = df[:,32]
svc = svm.SVC(kernel = 'rbf', gamma = 0.001, C = 8).fit(X,y)
print('Accuracy score is: ', accuracy_score(y, svc.predict(X)))

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

class Student:
    def __init__(self, name, email, math_score, science_score, english_score):
        self.name = name
        self.email = email
        self.math_score = math_score
        self.science_score = science_score
        self.english_score = english_score

    def average(self):
        return (self.math_score + self.science_score + self.english_score) / 3
    
    def print_email(self):
        print(f"{self.name}'s email is {self.email}")

def compute():
    X = np.array([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]])
    err = np.array([0.3, 0.2, 0.1])
    mx = np.mean(X, axis = 0)
    y = np.dot(err, X).reshape(4, 1)
    print(mx)
    print(y)

#compute()

def pandas():
    df = pd.read_csv("boston.csv")
    df.columns = ['CRIM', 'ZN', 'INDUS', 'CHAS', 'NOX', 'RM', 'AGE', 'DIS', 'RAD', 'TAX', 'PTRATIO', 'B', 'LSTAT', 'MEDV']
    df[df['CRIM'] < 1.0]
    print(np.mean(df.MEDV))

    plt.hist(df.MEDV, bins = 100)
    plt.show()

pandas()

def graph():
    x = np.arange(-2, 2, 0.2)
    plt.plot(x, x ** 3 + x, color = 'red')
    plt.show()

#graph()

def heart_disease():
    df = pd.read_csv("heart_disease.csv")
    df.columns = ['age', 'sex', 'cp', 'trestbps', 'chol', 'fbs', 'restecg', 'thalach', 'exang', 'oldpeak', 'slope', 'ca', 'thal', 'num']
    origin = df.values
    origin[origin[:,13] > 0, 13]= 1

    

#heart_disease()
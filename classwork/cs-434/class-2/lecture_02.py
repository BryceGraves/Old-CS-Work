# -*- coding: utf-8 -*-
"""Lecture 02.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1B6YZS8ymATwoAUYHGtiYleFoOUlE7eM4

# Data Processing

***
##### CS 434 - Dating Mining and Machine Learning
##### Oregon State University-Cascades
***

## <img src="https://img.icons8.com/color/32/000000/fork-lift.png"/> Load packages

Run this first everytime you restart.
"""

import pandas as pd
import numpy as np
import seaborn as sns
from io import StringIO
import matplotlib.pyplot as plt
from matplotlib.ticker import AutoMinorLocator
from IPython.display import display
from sklearn import preprocessing
from sklearn.impute import SimpleImputer
from sklearn.preprocessing import MinMaxScaler
from sklearn.preprocessing import StandardScaler

"""# <img src="https://img.icons8.com/color/32/000000/accept-database.png"/> Load data
Load a CSV file into a Pandas dataframe.
"""

csv_data = '''A,B,C,D
1.0,2.0,3.0,4.0
5.0,6.0,,8.0
10.0,11.0,12.0,
,,,'''

# Load csv data (from a file)
#df = pd.read_csv('csv_data.csv')

# Load csv data (from a string)
df = pd.read_csv(StringIO(csv_data))

print('Pandas view:')
display(df)
print()
print('Numpy view:')
display(df.values)

"""# <img src="https://img.icons8.com/color/32/000000/bank-card-missing.png"/>  Dealing with missing and incomplete data
Real data is messy and incomplete.

## <img src="https://img.icons8.com/color/32/000000/question-mark.png"/> Dealing with missing values

We can use `df.isnull()` to identify and count missing values.
"""

# count the total number of missing values
df.isnull().sum().sum()

# count the number of rows that are missing value(s)
df.shape[0] - df.dropna().shape[0]

# count the number of missing values by column (feature)
df.isnull().sum()

# count the number of missing values by row (example)
for i in range(len(df.index)):
    print("row ", i, " : ",  df.iloc[i].isnull().sum())

"""## <img src="https://img.icons8.com/color/32/000000/signal-horn.png"/> Dealing with noisy data
We can define a list of symbols to consider as missing data and convert those to `nan`.
"""

noisy_csv_data = '''A,B,C,D
A,B,C,D
1,2,3,4
5,6,,+
,10,?,12
-,14,n/a,na'''

# print original
display(pd.read_csv(StringIO(noisy_csv_data)))
print()

# list of missing values
missing = ['n/a', 'na', '-', '+', '?']

# Load csv data and convert missing values to nan
df_noisy = pd.read_csv(StringIO(noisy_csv_data), na_values=missing)
display(df_noisy)

"""## <img src="https://img.icons8.com/color/32/000000/remove-property.png"/> Eliminating training examples or features with missing values
We can eliminate rows (examples) and columns (features) that contain missing data.
"""

# remove rows that contain missing values
df.dropna(axis=0)

# remove columns that contain missing values
df.dropna(axis=1)

# only drop rows where all columns are NaN
df.dropna(how='all')

# drop rows that have fewer than N real values (here: N=3)
df.dropna(thresh=4)

# only drop rows where NaN appear in specific columns (here: 'C')
df.dropna(subset=['C'])

"""# <img src="https://img.icons8.com/color/32/000000/data-configuration.png"/>  Describing data"""

df_wine = pd.read_csv(
    'http://archive.ics.uci.edu/ml/machine-learning-databases/wine/wine.data', header=None)
df_wine.columns = ['Class label', 'Alcohol', 'Malic acid', 'Ash',
                   'Alcalinity of ash', 'Magnesium', 'Total phenols',
                   'Flavanoids', 'Nonflavanoid phenols', 'Proanthocyanins',
                   'Color intensity', 'Hue', 'OD280/OD315 of diluted wines',
                   'Proline']
# display the first five lines
df_wine.head()

"""## <img src="https://img.icons8.com/color/32/000000/page-size.png"/> Size and shape of data
We often need to know how many rows and columns are in the data.
"""

print('number of rows:    ', len(df_wine))
print('shape of data:     ', df_wine.shape)
print('number of examples:', df_wine.shape[0])
print('number of features:', df_wine.shape[1])

"""## <img src="https://img.icons8.com/color/32/000000/cosine.png"/> Visualize the data

We can examine the data of two attributes (here, 'Alchohol' and 'Hue') for each of the three classes.
"""

sns.lmplot('Alcohol', 'Hue', data=df_wine,  fit_reg=False, col='Class label')

"""Or we can view them in one plot."""

sns.lmplot('Alcohol', 'Hue', data=df_wine,  fit_reg=False, hue='Class label')

"""We can also compare each feature against each other feature (wait for it)."""

sns.pairplot(df_wine.loc[:, df_wine.dtypes == 'float64'])

"""## <img src="https://img.icons8.com/color/32/000000/details.png"/> Summary statistics
**Mean** is the numerical *average*. The mean of `[1,2,3,4]` is `(1+2+3+4)/4 = 2.5.`

**Median** is the *middle value*. The the median of `[1,3,10]` is `3`.

**Mode** is the *most frequent value*. The mode of `[1,3,3]` is `3`.

**Standard deviation** is a measure of *variation*. The stdev of `[1.7,2.1,1.5,1.6,1.9]` is `0.2154`.
"""

df_wine.describe()

"""## <img src="https://img.icons8.com/color/32/000000/categorize.png"/> Describing different types of data

### Numeric data
"""

# numeric data
df_num = pd.Series([3, 1, 4, 1, 5, 9])
df_num.describe()

"""### Categorical data"""

# categorial data
df_cat = pd.Series(['a', 'a', 'b', 'c', 'a', 'b'])
df_cat.describe()

"""### Time series data"""

# time series data
df_time = pd.Series([
    np.datetime64("2012-12-10"),
    np.datetime64("2018-01-01"),
    np.datetime64("2018-01-01")
])
df_time.describe()

"""## <img src="https://img.icons8.com/color/32/000000/data-recovery.png"/> Add summary statistics to a dataframe"""

# generate df with random values
vals = np.random.rand(3, 3)
df_rand = pd.DataFrame(vals)
df_rand.columns = ['sensor1', 'sensor2', 'sensor3']
display(df_rand)

# add columns with summary statistics (across each example)
df_rand['mean'] = df_rand.mean(numeric_only=True, axis=1)
df_rand['median'] = df_rand.median(numeric_only=True, axis=1)
df_rand['stdev'] = df_rand.std(numeric_only=True, axis=1)
display(df_rand)

df_rand = df_rand.drop(columns=['mean', 'median', 'stdev'])

# add row with summary statistics (across each feature)
df_rand.loc['mean'] = df_rand.mean()
df_rand.loc['median'] = df_rand.median()
df_rand.loc['stdev'] = df_rand.std()
display(df_rand)

"""# <img src="https://img.icons8.com/color/32/000000/add-subnode.png"/>  Imputing missing values
Instead of throwing away features and examples that are missing values, we can substitute in the feature's mean for the missing value.
"""

# original data
display(df)

# impute missing values via the column mean
# numpy approach
imr = SimpleImputer(missing_values=np.nan, strategy='mean')
imr = imr.fit(df.values)
imputed_data = imr.transform(df.values)
display(imputed_data)

# impute missing values via the column mean
# Pandas approach
display(df.fillna(df.mean()))

# impute missing values via the column median
# Pandas approach
display(df.fillna(df.median()))

"""***

# <img src="https://img.icons8.com/color/32/000000/chat.png"/> Discussion

1. Why is real world data messy and incomplete?

2. Dropping examples or features with missing values is easy. Is it always the right thing to do?

3. When might it make sense (for what types of data) to calculate the mean/median/stdev for each example and add as a new feature?

4. For non-numeric (string) data, how should we handle missing data?

5. When might you prefer to impute the *median* rather than the *mean*?

---
"""

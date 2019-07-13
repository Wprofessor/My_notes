import nltk
from nltk.corpus import stopwords
from nltk.stem.snowball import SnowballStemmer

# stemmer = SnowballStemmer("english")
# stemmer.stem("responsiveness")
# stemmer.stem("responsivity")
# stemmer.stem("unresponsive")

# nltk.download()
words = stopwords.words('english')
print(len(words))
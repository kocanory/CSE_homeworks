prescript(X, tamiflu):-fever(X, high), group(X, highRisk).
prescript(X, aspirin):-fever(X, high), group(X, lowRisk).
group(X, highRisk):-age(X, old), bp(X, high).
group(X, highRisk):-has(X, heartDisease).
group(X, lowRisk):-age(X, young).
age(kim, young).
fever(kim, high).
bp(kim, high).
has(kim, stomachDisorder).

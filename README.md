# HIV-HPV Model
Stochastic microsimulation model of HIV/HPV co-infection and carcinogenesis in South African women.

This document describes an incidence-based stochastic microsimulation of HIV-HPV co-infection and cervical cancer carcinogenesis in South African women. Over the course of her lifetime, each woman has an age-specific risk of acquiring HIV and HPV infections. A woman may acquire HIV infection at any stage of her life, and this happens at the beginning of the month after she is subject to background mortality. Her risk of HIV is exogenous to the model and simply a function of age. A woman can only acquire HPV if she is healthy, and her risk is a function of age, HIV status, and history of infection. While most HPV infections clear naturally, some oncogenic HPV infections can progress to CIN 2, CIN 3, cervical cancer and death from cervical cancer. A woman dies from cervical cancer if this precedes death from other causes.

Screening can change the simulated woman’s life history. In the model, each simulated life history is considered in situations with different screening strategies, which vary by age to start screening, frequency of screen, screen test and age to stop screening. In each life history, a screening test (cytology or HPV test) can be applied at certain ages. If a screening test is applied, each HPV-infection/lesion prevalent at the time of the screen has a probability (i.e. sensitivity) of producing a positive test. Based on the result of the test. Based on the result of the test, a woman can either be advised to attend another test or be referred to colposcopy and treatment. If a woman attends colposcopy and treatment, it is assumed all prevalent CIN-lesions are removed and can no longer lead to cervical cancer. HPV-infections without CIN are not treated. For screen-detected cervical cancer, a stage-specific improvement (compared to the situation without screening) in the probability of a cure is assumed.

**Policy question:**
What are the optimal cervical cancer screening strategies for HIV positive and negative women (w.r.t. interval/frequency of screen, age to start and end screening and screening test)?

**Health States**
1) Healthy
2) HIV
3) HPV (genotype-specific)
4) CIN-2
5) CIN-3
6) Cervical Cancer (stage specific) 
7) HIV-HPV (genotype-specific) 
8) HIV-CIN-2
9) HIV-CIN-3
10) HIV-Cervical Cancer (stage specific) 
11) Dead Cancer
12) Dead Other Causes

**Attributes**
1) Age
2) History 
3) CD4
4) Viral load 
5) ART

**Data Sources**
ave
1) HIV incidence (by age): Thembisa Model 2014
2) HPV incidence (by age, genotype)
3) Cancer mortality (by duration, stage, detected vs undetected vs screen)
4) Background mortality (by age): mSankar
5) Excess mortality rate for HIV (by CD4 at ART initiation and time on ART): GOALS model
6) ARV coverage (by age) (HSRC 2014)
7) CD4decline from current level if not on ART (by age): GOALS model
8) Starting CD4 distribution at seroconversion (by age): GOALS model

**Model Assumptions**
1) HIV is exogenous HIV incidence is independent of HPV/CC
2) HPV incidence, persistence, CIN persistence and CC varies by HIV positivity, CD4, ART

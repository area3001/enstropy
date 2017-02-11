## enstropy

This firmware provides full-speed USB access to the Nucleo-L053R8's TRNG. Single buffering combined with only tx'ing one 32-bit random number at a time gives us a 900kbps TRNG data stream.

We've checked the resulting TRNG stream against the [NIST](http://csrc.nist.gov/groups/ST/toolkit/rng/index.html) and [Dieharder](https://www.phy.duke.edu/~rgb/General/dieharder.php) RNG statistical test suites. Contrary to ST's own test results mentioned in [AN4230](http://www.st.com/resource/en/application_note/dm00073853.pdf), the STM32L053's TNRG failed both tests on our setup, see the output below. We have not pinpointed the root cause of this issue yet. We welcome any review of our code base, especially the RNG init code, as well as re-running the statistical test suites.

```
~/dev/nist/sts-2.1.2 $ ./assess 800000
~/dev/nist/sts-2.1.2 $ cat experiments/AlgorithmTesting/finalAnalysisReport.txt 
------------------------------------------------------------------------------
RESULTS FOR THE UNIFORMITY OF P-VALUES AND THE PROPORTION OF PASSING SEQUENCES
------------------------------------------------------------------------------
   generator is <../enstropy>
------------------------------------------------------------------------------
 C1  C2  C3  C4  C5  C6  C7  C8  C9 C10  P-VALUE  PROPORTION  STATISTICAL TEST
------------------------------------------------------------------------------
  8   1   0   1   0   0   0   0   0   0  0.000000 *    5/10   *  Frequency
  1   1   2   0   1   0   0   1   2   2  0.739918     10/10      BlockFrequency
  9   0   0   0   1   0   0   0   0   0  0.000000 *    5/10   *  CumulativeSums
  8   1   1   0   0   0   0   0   0   0  0.000000 *    4/10   *  CumulativeSums
  3   1   1   1   2   0   2   0   0   0  0.350485      9/10      Runs
  1   1   0   1   2   2   1   1   1   0  0.911413     10/10      LongestRun
  1   1   2   1   1   2   0   2   0   0  0.739918      9/10      Rank
  3   2   1   0   0   1   0   1   0   2  0.350485      9/10      FFT
  2   0   1   1   1   2   0   1   1   1  0.911413     10/10      NonOverlappingTemplate
  0   3   2   2   0   0   0   0   1   2  0.213309     10/10      NonOverlappingTemplate
  1   0   2   1   1   0   1   2   2   0  0.739918     10/10      NonOverlappingTemplate
  2   0   1   2   2   1   0   1   1   0  0.739918     10/10      NonOverlappingTemplate
  3   1   2   1   0   1   0   0   1   1  0.534146     10/10      NonOverlappingTemplate
  4   0   1   2   0   0   0   1   0   2  0.066882     10/10      NonOverlappingTemplate
  0   3   0   2   2   1   0   0   2   0  0.213309     10/10      NonOverlappingTemplate
  0   1   0   2   1   2   2   1   0   1  0.739918     10/10      NonOverlappingTemplate
 10   0   0   0   0   0   0   0   0   0  0.000000 *    0/10   *  NonOverlappingTemplate
  9   0   1   0   0   0   0   0   0   0  0.000000 *    2/10   *  NonOverlappingTemplate
  1   1   1   0   1   1   0   0   0   5  0.017912      9/10      NonOverlappingTemplate
  1   2   1   0   2   1   0   1   1   1  0.911413     10/10      NonOverlappingTemplate
  1   1   4   0   1   1   1   1   0   0  0.213309     10/10      NonOverlappingTemplate
  0   0   1   3   2   1   0   0   2   1  0.350485     10/10      NonOverlappingTemplate
  2   1   1   1   1   0   0   1   1   2  0.911413     10/10      NonOverlappingTemplate
  0   2   2   1   0   0   1   1   2   1  0.739918     10/10      NonOverlappingTemplate
 10   0   0   0   0   0   0   0   0   0  0.000000 *    1/10   *  NonOverlappingTemplate
  1   2   0   0   0   1   4   1   1   0  0.122325     10/10      NonOverlappingTemplate
 10   0   0   0   0   0   0   0   0   0  0.000000 *    1/10   *  NonOverlappingTemplate
  1   1   0   1   0   1   2   2   1   1  0.911413     10/10      NonOverlappingTemplate
  1   0   1   3   1   1   2   0   0   1  0.534146     10/10      NonOverlappingTemplate
  1   1   2   1   1   1   0   1   0   2  0.911413     10/10      NonOverlappingTemplate
  0   1   2   0   0   1   3   0   2   1  0.350485     10/10      NonOverlappingTemplate
  2   1   1   0   2   1   0   2   1   0  0.739918     10/10      NonOverlappingTemplate
  2   1   0   1   2   1   0   1   2   0  0.739918     10/10      NonOverlappingTemplate
  0   1   1   0   1   2   0   1   0   4  0.122325     10/10      NonOverlappingTemplate
  0   2   2   1   0   3   0   0   1   1  0.350485     10/10      NonOverlappingTemplate
  1   2   2   0   2   1   0   0   2   0  0.534146     10/10      NonOverlappingTemplate
  1   1   0   0   1   0   3   0   2   2  0.350485     10/10      NonOverlappingTemplate
  0   1   1   0   2   2   3   0   1   0  0.350485     10/10      NonOverlappingTemplate
  0   3   0   1   3   0   0   0   3   0  0.035174     10/10      NonOverlappingTemplate
  3   1   4   0   0   0   1   0   1   0  0.035174     10/10      NonOverlappingTemplate
  4   0   1   1   2   0   0   1   0   1  0.122325     10/10      NonOverlappingTemplate
  0   1   2   3   2   0   0   0   2   0  0.213309     10/10      NonOverlappingTemplate
  4   4   1   0   0   0   0   1   0   0  0.004301     10/10      NonOverlappingTemplate
  7   1   1   0   0   0   0   0   1   0  0.000003 *   10/10      NonOverlappingTemplate
  1   1   0   2   1   1   1   0   1   2  0.911413     10/10      NonOverlappingTemplate
  2   0   1   1   1   0   1   3   1   0  0.534146     10/10      NonOverlappingTemplate
  1   0   2   2   2   0   2   1   0   0  0.534146     10/10      NonOverlappingTemplate
  1   0   0   2   1   0   1   1   2   2  0.739918     10/10      NonOverlappingTemplate
  2   0   0   1   0   2   1   0   4   0  0.066882     10/10      NonOverlappingTemplate
  1   1   2   1   2   0   2   1   0   0  0.739918     10/10      NonOverlappingTemplate
  0   4   1   1   0   1   1   0   2   0  0.122325     10/10      NonOverlappingTemplate
  0   2   2   2   1   0   1   1   1   0  0.739918     10/10      NonOverlappingTemplate
  0   3   2   1   1   0   0   2   1   0  0.350485     10/10      NonOverlappingTemplate
  0   0   1   2   3   2   0   1   1   0  0.350485     10/10      NonOverlappingTemplate
  1   2   1   0   2   0   0   1   1   2  0.739918      9/10      NonOverlappingTemplate
  2   0   2   0   1   0   2   0   1   2  0.534146     10/10      NonOverlappingTemplate
  1   0   2   1   1   1   2   0   1   1  0.911413     10/10      NonOverlappingTemplate
  1   1   0   0   3   3   0   0   1   1  0.213309     10/10      NonOverlappingTemplate
  1   1   1   1   2   0   1   1   0   2  0.911413     10/10      NonOverlappingTemplate
  1   1   0   1   0   1   1   2   2   1  0.911413     10/10      NonOverlappingTemplate
  2   2   1   1   1   0   1   1   1   0  0.911413      9/10      NonOverlappingTemplate
  1   2   0   0   0   1   3   2   0   1  0.350485     10/10      NonOverlappingTemplate
  1   3   1   1   1   1   0   1   1   0  0.739918     10/10      NonOverlappingTemplate
  1   2   1   2   0   2   0   1   1   0  0.739918     10/10      NonOverlappingTemplate
  1   0   2   0   2   2   0   1   1   1  0.739918     10/10      NonOverlappingTemplate
  2   1   0   2   0   0   4   1   0   0  0.066882      9/10      NonOverlappingTemplate
  1   1   0   2   3   0   2   1   0   0  0.350485     10/10      NonOverlappingTemplate
  2   1   1   3   1   0   0   1   0   1  0.534146     10/10      NonOverlappingTemplate
  2   0   0   0   0   0   2   1   3   2  0.213309     10/10      NonOverlappingTemplate
  2   0   2   1   1   1   0   2   1   0  0.739918     10/10      NonOverlappingTemplate
  0   1   2   1   1   2   2   0   0   1  0.739918     10/10      NonOverlappingTemplate
  1   0   0   3   1   1   1   1   1   1  0.739918      9/10      NonOverlappingTemplate
  0   1   1   0   1   1   4   1   1   0  0.213309     10/10      NonOverlappingTemplate
  0   2   1   1   3   1   0   1   1   0  0.534146     10/10      NonOverlappingTemplate
  2   1   1   1   1   1   1   0   2   0  0.911413     10/10      NonOverlappingTemplate
  0   1   1   1   0   1   3   1   1   1  0.739918     10/10      NonOverlappingTemplate
  0   1   2   1   1   1   1   1   2   0  0.911413     10/10      NonOverlappingTemplate
  3   0   1   1   1   3   0   0   1   0  0.213309     10/10      NonOverlappingTemplate
  4   3   0   1   0   0   0   1   1   0  0.035174      9/10      NonOverlappingTemplate
  2   0   0   1   1   2   2   1   0   1  0.739918      8/10      NonOverlappingTemplate
  2   1   0   1   1   1   1   0   2   1  0.911413      9/10      NonOverlappingTemplate
  2   1   0   1   0   3   2   0   0   1  0.350485     10/10      NonOverlappingTemplate
  2   0   1   1   1   2   0   1   1   1  0.911413     10/10      NonOverlappingTemplate
  1   0   2   0   2   0   1   2   1   1  0.739918     10/10      NonOverlappingTemplate
  0   1   2   1   1   2   1   1   1   0  0.911413     10/10      NonOverlappingTemplate
  2   1   1   2   1   0   0   0   0   3  0.350485     10/10      NonOverlappingTemplate
  3   1   3   1   0   0   0   1   0   1  0.213309     10/10      NonOverlappingTemplate
  1   2   2   0   2   0   0   1   1   1  0.739918     10/10      NonOverlappingTemplate
  0   1   0   2   0   2   1   0   0   4  0.066882     10/10      NonOverlappingTemplate
  3   2   1   0   1   0   1   2   0   0  0.350485      8/10      NonOverlappingTemplate
  1   1   1   0   0   1   1   0   3   2  0.534146      9/10      NonOverlappingTemplate
  1   1   1   1   1   1   1   1   2   0  0.991468     10/10      NonOverlappingTemplate
  1   1   0   3   0   2   1   1   0   1  0.534146     10/10      NonOverlappingTemplate
  0   0   1   3   0   0   1   2   2   1  0.350485     10/10      NonOverlappingTemplate
  1   1   1   0   1   1   0   2   2   1  0.911413     10/10      NonOverlappingTemplate
  1   1   1   0   1   4   0   0   1   1  0.213309      9/10      NonOverlappingTemplate
  1   2   0   1   3   0   2   0   1   0  0.350485     10/10      NonOverlappingTemplate
  0   1   1   1   2   2   1   1   0   1  0.911413     10/10      NonOverlappingTemplate
  1   3   0   0   0   2   0   2   0   2  0.213309     10/10      NonOverlappingTemplate
  0   2   0   1   2   1   0   2   1   1  0.739918     10/10      NonOverlappingTemplate
  0   0   2   1   2   2   0   0   1   2  0.534146     10/10      NonOverlappingTemplate
  1   2   0   2   2   1   0   0   1   1  0.739918     10/10      NonOverlappingTemplate
  2   0   0   0   1   2   2   0   3   0  0.213309      9/10      NonOverlappingTemplate
  2   0   0   3   1   1   0   2   0   1  0.350485     10/10      NonOverlappingTemplate
  2   2   2   0   2   0   1   0   1   0  0.534146     10/10      NonOverlappingTemplate
  2   2   0   1   1   2   1   0   1   0  0.739918     10/10      NonOverlappingTemplate
  6   1   0   1   1   0   0   1   0   0  0.000439     10/10      NonOverlappingTemplate
  1   6   0   2   0   0   0   0   1   0  0.000199     10/10      NonOverlappingTemplate
  2   2   1   3   1   1   0   0   0   0  0.350485     10/10      NonOverlappingTemplate
  0   2   1   1   2   2   1   0   1   0  0.739918     10/10      NonOverlappingTemplate
  3   0   2   0   0   2   0   1   1   1  0.350485      9/10      NonOverlappingTemplate
  0   4   2   0   1   0   1   0   0   2  0.066882     10/10      NonOverlappingTemplate
  0   0   2   1   0   1   3   0   1   2  0.350485     10/10      NonOverlappingTemplate
  2   2   0   2   0   1   0   0   2   1  0.534146     10/10      NonOverlappingTemplate
  0   0   0   2   0   0   3   1   1   3  0.122325     10/10      NonOverlappingTemplate
  3   1   1   1   1   0   0   1   0   2  0.534146     10/10      NonOverlappingTemplate
  0   1   3   1   1   0   1   1   0   2  0.534146     10/10      NonOverlappingTemplate
  0   1   1   0   1   2   2   3   0   0  0.350485     10/10      NonOverlappingTemplate
  2   2   0   0   2   1   1   0   0   2  0.534146      9/10      NonOverlappingTemplate
  2   1   0   1   1   1   3   1   0   0  0.534146     10/10      NonOverlappingTemplate
  1   1   1   0   2   2   1   0   0   2  0.739918     10/10      NonOverlappingTemplate
  0   2   0   0   1   2   1   2   1   1  0.739918     10/10      NonOverlappingTemplate
  0   1   2   0   1   0   2   3   0   1  0.350485     10/10      NonOverlappingTemplate
  0   0   3   2   2   1   1   1   0   0  0.350485     10/10      NonOverlappingTemplate
  1   2   0   0   0   1   2   3   1   0  0.350485      9/10      NonOverlappingTemplate
  0   2   1   0   2   2   0   1   2   0  0.534146     10/10      NonOverlappingTemplate
  2   0   2   0   0   1   1   3   0   1  0.350485     10/10      NonOverlappingTemplate
  0   1   0   2   0   2   2   3   0   0  0.213309     10/10      NonOverlappingTemplate
  6   1   0   0   2   0   0   1   0   0  0.000199      9/10      NonOverlappingTemplate
  2   1   1   2   0   1   0   1   1   1  0.911413     10/10      NonOverlappingTemplate
  1   1   2   0   1   2   0   1   2   0  0.739918     10/10      NonOverlappingTemplate
  2   0   1   1   0   1   1   1   0   3  0.534146     10/10      NonOverlappingTemplate
  0   0   0   0   3   1   5   0   1   0  0.002043     10/10      NonOverlappingTemplate
  0   1   0   2   1   3   0   0   2   1  0.350485     10/10      NonOverlappingTemplate
  3   1   1   1   0   1   0   2   1   0  0.534146     10/10      NonOverlappingTemplate
  2   1   0   2   2   0   1   2   0   0  0.534146     10/10      NonOverlappingTemplate
  2   1   0   1   1   1   2   0   1   1  0.911413     10/10      NonOverlappingTemplate
  2   0   0   0   2   0   3   0   0   3  0.066882     10/10      NonOverlappingTemplate
  0   1   2   0   1   3   1   1   1   0  0.534146     10/10      NonOverlappingTemplate
  0   2   1   0   1   2   1   1   0   2  0.739918     10/10      NonOverlappingTemplate
  0   2   0   1   3   1   1   1   1   0  0.534146     10/10      NonOverlappingTemplate
  2   1   0   0   1   1   2   0   0   3  0.350485      9/10      NonOverlappingTemplate
  0   0   0   0   2   2   1   4   1   0  0.066882     10/10      NonOverlappingTemplate
  0   0   0   0   1   2   2   2   3   0  0.213309     10/10      NonOverlappingTemplate
  0   0   1   0   1   1   2   0   2   3  0.350485     10/10      NonOverlappingTemplate
  0   1   1   1   1   0   3   0   3   0  0.213309     10/10      NonOverlappingTemplate
  1   3   0   0   1   1   1   1   0   2  0.534146     10/10      NonOverlappingTemplate
  2   0   2   0   2   2   0   1   1   0  0.534146     10/10      NonOverlappingTemplate
  0   0   2   2   1   2   0   1   0   2  0.534146     10/10      NonOverlappingTemplate
  0   2   0   0   3   1   0   1   1   2  0.350485     10/10      NonOverlappingTemplate
  0   2   0   0   0   1   3   1   1   2  0.350485     10/10      NonOverlappingTemplate
  1   2   1   0   0   3   0   0   3   0  0.122325     10/10      NonOverlappingTemplate
  1   1   2   0   0   0   2   2   0   2  0.534146     10/10      NonOverlappingTemplate
  0   1   2   0   0   2   2   1   2   0  0.534146     10/10      NonOverlappingTemplate
  3   0   1   1   1   1   1   0   0   2  0.534146     10/10      NonOverlappingTemplate
  2   1   0   1   0   3   2   0   0   1  0.350485     10/10      NonOverlappingTemplate
  2   0   3   0   1   0   2   1   0   1  0.350485     10/10      OverlappingTemplate
  0   1   0   0   1   1   1   1   1   4  0.213309     10/10      Universal
  7   2   1   0   0   0   0   0   0   0  0.000001 *    7/10   *  ApproximateEntropy
  0   0   1   0   1   1   0   0   0   0     ----       3/3       RandomExcursions
  0   0   0   0   2   0   0   0   0   1     ----       3/3       RandomExcursions
  1   0   0   0   1   0   0   0   1   0     ----       3/3       RandomExcursions
  1   0   0   0   0   0   0   1   1   0     ----       3/3       RandomExcursions
  0   1   0   0   0   0   1   0   1   0     ----       3/3       RandomExcursions
  1   0   1   0   0   1   0   0   0   0     ----       3/3       RandomExcursions
  2   0   0   0   0   0   1   0   0   0     ----       3/3       RandomExcursions
  1   0   1   1   0   0   0   0   0   0     ----       2/3       RandomExcursions
  1   0   0   0   0   0   0   1   0   1     ----       3/3       RandomExcursionsVariant
  1   0   0   0   0   0   1   0   0   1     ----       3/3       RandomExcursionsVariant
  1   0   0   0   1   0   0   1   0   0     ----       3/3       RandomExcursionsVariant
  1   0   0   1   0   0   1   0   0   0     ----       3/3       RandomExcursionsVariant
  0   1   0   1   1   0   0   0   0   0     ----       3/3       RandomExcursionsVariant
  0   1   1   1   0   0   0   0   0   0     ----       3/3       RandomExcursionsVariant
  0   0   1   2   0   0   0   0   0   0     ----       3/3       RandomExcursionsVariant
  0   0   0   2   0   0   0   1   0   0     ----       3/3       RandomExcursionsVariant
  0   0   1   1   0   0   0   0   0   1     ----       3/3       RandomExcursionsVariant
  1   0   0   1   0   0   0   0   0   1     ----       3/3       RandomExcursionsVariant
  1   1   1   0   0   0   0   0   0   0     ----       3/3       RandomExcursionsVariant
  2   0   1   0   0   0   0   0   0   0     ----       3/3       RandomExcursionsVariant
  2   0   1   0   0   0   0   0   0   0     ----       3/3       RandomExcursionsVariant
  2   0   1   0   0   0   0   0   0   0     ----       3/3       RandomExcursionsVariant
  1   1   1   0   0   0   0   0   0   0     ----       3/3       RandomExcursionsVariant
  1   1   0   1   0   0   0   0   0   0     ----       3/3       RandomExcursionsVariant
  1   1   0   0   0   1   0   0   0   0     ----       3/3       RandomExcursionsVariant
  1   1   0   0   0   0   1   0   0   0     ----       3/3       RandomExcursionsVariant
  2   4   0   3   0   1   0   0   0   0  0.017912      9/10      Serial
  2   0   3   0   1   2   1   1   0   0  0.350485     10/10      Serial
  1   2   1   1   0   1   2   0   2   0  0.739918     10/10      LinearComplexity


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
The minimum pass rate for each statistical test with the exception of the
random excursion (variant) test is approximately = 8 for a
sample size = 10 binary sequences.

The minimum pass rate for the random excursion (variant) test
is approximately = 2 for a sample size = 3 binary sequences.

For further guidelines construct a probability table using the MAPLE program
provided in the addendum section of the documentation.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
```

```
~$ cat /dev/enstropy/trng | dieharder -g 200 -a
#=============================================================================#
#            dieharder version 3.31.1 Copyright 2003 Robert G. Brown          #
#=============================================================================#
   rng_name    |rands/second|   Seed   |
stdin_input_raw|  2.45e+04  |2522282488|
#=============================================================================#
        test_name   |ntup| tsamples |psamples|  p-value |Assessment
#=============================================================================#
   diehard_birthdays|   0|       100|     100|0.92660438|  PASSED  
      diehard_operm5|   0|   1000000|     100|0.26321675|  PASSED  
  diehard_rank_32x32|   0|     40000|     100|0.23105295|  PASSED  
    diehard_rank_6x8|   0|    100000|     100|0.44462886|  PASSED  
   diehard_bitstream|   0|   2097152|     100|0.00000000|  FAILED  
        diehard_opso|   0|   2097152|     100|0.00000000|  FAILED  
        diehard_oqso|   0|   2097152|     100|0.00000289|   WEAK   
         diehard_dna|   0|   2097152|     100|0.12586501|  PASSED  
diehard_count_1s_str|   0|    256000|     100|0.11503141|  PASSED  
diehard_count_1s_byt|   0|    256000|     100|0.23014826|  PASSED  
 diehard_parking_lot|   0|     12000|     100|0.00010297|   WEAK   
    diehard_2dsphere|   2|      8000|     100|0.84461897|  PASSED  
    diehard_3dsphere|   3|      4000|     100|0.93411614|  PASSED  
     diehard_squeeze|   0|    100000|     100|0.00000000|  FAILED  
        diehard_sums|   0|       100|     100|0.04960378|  PASSED  
        diehard_runs|   0|    100000|     100|0.90065589|  PASSED  
        diehard_runs|   0|    100000|     100|0.51248519|  PASSED  
       diehard_craps|   0|    200000|     100|0.00000000|  FAILED  
       diehard_craps|   0|    200000|     100|0.00000000|  FAILED  
 marsaglia_tsang_gcd|   0|  10000000|     100|0.00000000|  FAILED  
 marsaglia_tsang_gcd|   0|  10000000|     100|0.00000000|  FAILED  
         sts_monobit|   1|    100000|     100|0.00000000|  FAILED  
            sts_runs|   2|    100000|     100|0.00000000|  FAILED  
          sts_serial|   1|    100000|     100|0.00000000|  FAILED  
          sts_serial|   2|    100000|     100|0.00000000|  FAILED  
          sts_serial|   3|    100000|     100|0.00000000|  FAILED  
          sts_serial|   3|    100000|     100|0.00000000|  FAILED  
          sts_serial|   4|    100000|     100|0.00000000|  FAILED  
          sts_serial|   4|    100000|     100|0.00000000|  FAILED  
          sts_serial|   5|    100000|     100|0.00000000|  FAILED  
          sts_serial|   5|    100000|     100|0.00000000|  FAILED  
          sts_serial|   6|    100000|     100|0.00000000|  FAILED  
          sts_serial|   6|    100000|     100|0.00000000|  FAILED  
          sts_serial|   7|    100000|     100|0.00000000|  FAILED  
          sts_serial|   7|    100000|     100|0.00000000|  FAILED  
          sts_serial|   8|    100000|     100|0.00000000|  FAILED  
          sts_serial|   8|    100000|     100|0.00000000|  FAILED  
          sts_serial|   9|    100000|     100|0.00000000|  FAILED  
          sts_serial|   9|    100000|     100|0.49134385|  PASSED  
          sts_serial|  10|    100000|     100|0.00000000|  FAILED  
          sts_serial|  10|    100000|     100|0.77103873|  PASSED  
          sts_serial|  11|    100000|     100|0.00000000|  FAILED  
          sts_serial|  11|    100000|     100|0.73439962|  PASSED  
          sts_serial|  12|    100000|     100|0.00000000|  FAILED  
          sts_serial|  12|    100000|     100|0.19070933|  PASSED  
          sts_serial|  13|    100000|     100|0.00000000|  FAILED  
          sts_serial|  13|    100000|     100|0.46151773|  PASSED  
          sts_serial|  14|    100000|     100|0.00000000|  FAILED  
          sts_serial|  14|    100000|     100|0.72747408|  PASSED  
          sts_serial|  15|    100000|     100|0.00000000|  FAILED  
          sts_serial|  15|    100000|     100|0.64029669|  PASSED  
          sts_serial|  16|    100000|     100|0.00000000|  FAILED  
          sts_serial|  16|    100000|     100|0.31405645|  PASSED  
         rgb_bitdist|   1|    100000|     100|0.00000000|  FAILED  
         rgb_bitdist|   2|    100000|     100|0.00000000|  FAILED  
         rgb_bitdist|   3|    100000|     100|0.00000000|  FAILED  
         rgb_bitdist|   4|    100000|     100|0.00000000|  FAILED  
         rgb_bitdist|   5|    100000|     100|0.00000000|  FAILED  
         rgb_bitdist|   6|    100000|     100|0.00000000|  FAILED  
         rgb_bitdist|   7|    100000|     100|0.00000000|  FAILED  
         rgb_bitdist|   8|    100000|     100|0.00013796|   WEAK   
         rgb_bitdist|   9|    100000|     100|0.00103559|   WEAK   
         rgb_bitdist|  10|    100000|     100|0.00000126|   WEAK   
         rgb_bitdist|  11|    100000|     100|0.00536828|  PASSED  
         rgb_bitdist|  12|    100000|     100|0.00000757|   WEAK   
rgb_minimum_distance|   2|     10000|    1000|0.00081201|   WEAK   
rgb_minimum_distance|   3|     10000|    1000|0.10560191|  PASSED  
rgb_minimum_distance|   4|     10000|    1000|0.22490636|  PASSED  
rgb_minimum_distance|   5|     10000|    1000|0.18631075|  PASSED  
    rgb_permutations|   2|    100000|     100|0.63677589|  PASSED  
    rgb_permutations|   3|    100000|     100|0.67027825|  PASSED  
    rgb_permutations|   4|    100000|     100|0.96419252|  PASSED  
    rgb_permutations|   5|    100000|     100|0.31276921|  PASSED  
      rgb_lagged_sum|   0|   1000000|     100|0.00000000|  FAILED  
      rgb_lagged_sum|   1|   1000000|     100|0.00000000|  FAILED  
      rgb_lagged_sum|   2|   1000000|     100|0.00000000|  FAILED  
      rgb_lagged_sum|   3|   1000000|     100|0.00000000|  FAILED  
      rgb_lagged_sum|   4|   1000000|     100|0.00000000|  FAILED  
      rgb_lagged_sum|   5|   1000000|     100|0.00000000|  FAILED  
      rgb_lagged_sum|   6|   1000000|     100|0.00000000|  FAILED  
      rgb_lagged_sum|   7|   1000000|     100|0.00000000|  FAILED  
      rgb_lagged_sum|   8|   1000000|     100|0.00000000|  FAILED  
      rgb_lagged_sum|   9|   1000000|     100|0.00000000|  FAILED  
      rgb_lagged_sum|  10|   1000000|     100|0.00000000|  FAILED  
      rgb_lagged_sum|  11|   1000000|     100|0.00000000|  FAILED  
      rgb_lagged_sum|  12|   1000000|     100|0.00000000|  FAILED  
      rgb_lagged_sum|  13|   1000000|     100|0.00000000|  FAILED  
      rgb_lagged_sum|  14|   1000000|     100|0.00000000|  FAILED  
      rgb_lagged_sum|  15|   1000000|     100|0.00000000|  FAILED  
```


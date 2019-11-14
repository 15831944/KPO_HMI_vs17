This utility program is used to convert the parameter tables from the old style (AREA)
to the new style (UNITGROUPNO). Specialization is not done during convert. We will have
entries for the UNITGROUPNO like e.g. HMD = 10 or EAF = 20.
Specialization to 11, 12, 21 has to be done via the HMI.

The mapping between the Area and the corresponding UnitGroupNo is done with entries in
the file ParameterConverter.ini, e.g.

[EAF]
UnitGroupNo = 20

This provides a flexible solution in cas the mapping will change.

The entry for the tables gives the possibility to work on temporary tables for during test.

These tables can be created with sql statements like,

CREATE TABLE GT_PARAM_TEST AS SELECT * FROM GT_PARAM;

[PARAM_TABLES]
SourceParamTable = GT_PARAM_TEST
SourceParamMatrixTable = GT_PARAM_MATRIX_TEST
DestinationParamTable = GT_PARAM_TMP
DestinationParamMatrixTable = GT_PARAM_MATRIX_TMP

After creation of the new tables the old ones can be deleted and then created with the sql scripts
provided also in this solution.

During conversion additional checks are done:

1. Specialised parameter, e.g. EAF_1 are generalised to EAF. This can lead to constraint violation
   in case the general parameter exists.

2. Additional practice pointer will be recognized.

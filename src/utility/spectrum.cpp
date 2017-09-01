#include "spectrum.hpp"

//lookup tables for spectrum to XYZ
//taken from http://www.brucelindbloom.com/index.html?Eqn_Spect_to_XYZ.html
#if HQ_SPECTRUM==0
const float X[SPECTRUM_SAMPLES] =
{
    0.704719194064694f,
    8.05919368162368f,
    26.0397303584315f,
    26.3344474095872f,
    9.09217349249588f,
    0.468913675410046f,
    6.14434813643801f,
    29.2570087297861f,
    59.45f,
    90.6445191071685f,
    103.784866140455f,
    84.6507668018606f,
    44.2958425675426f,
    16.1994298557152f,
    4.63907953796373f,
    1.04114730065218f
};

const float Y[SPECTRUM_SAMPLES] =
{
    0.0195016632319789f,
    0.239892653121705f,
    1.71963304882257f,
    5.43351734723257f,
    13.2161643551524f,
    30.9100239096826f,
    68.950326803714f,
    96.1129005792559f,
    99.5f,
    86.0643147694386f,
    61.6534085244091f,
    37.7458551420146f,
    17.3069266562178f,
    5.99251195390313f,
    1.6862166377033f,
    0.37597729297547f
};

const float Z[SPECTRUM_SAMPLES] =
{
    3.34138395279395f,
    38.7186742138432f,
    130.621831055477f,
    151.16045260001f,
    77.2844348592836f,
    26.0294938186801f,
    7.59910194772867f,
    2.0451696873783f,
    0.39f,
    0.163225523487228f,
    0.0781659696030543f,
    0.0188233923280388f,
    0.00197793447499632f,
    0.f,
    0.f,
    0.f
};

constexpr const float INVY_SUM = 1.f/526.927171336876f;

const float spectrumWhite[] =
{
    1.06169892758108E+00f,
    1.06185235173098E+00f,
    1.06235480918019E+00f,
    1.06243224675144E+00f,
    1.06247071380683E+00f,
    1.06169309129124E+00f,
    1.06121012971027E+00f,
    1.06172757587078E+00f,
    1.06249074713985E+00f,
    1.06247634025206E+00f,
    1.06251442175581E+00f,
    1.06246246111650E+00f,
    1.06244537285346E+00f,
    1.06032701141155E+00f,
    1.06011790363707E+00f,
    1.06039144015336E+00f
};

const float spectrumWhiteL[SPECTRUM_SAMPLES] =
{
    1.15662285252444E+00f,
    1.15609926191619E+00f,
    1.15649247607115E+00f,
    1.15678503201471E+00f,
    1.15653089427314E+00f,
    1.15647351579360E+00f,
    1.15205854350223E+00f,
    1.13165968156162E+00f,
    1.08976900762109E+00f,
    1.01981823795452E+00f,
    9.40345756494529E-01f,
    9.07197061802526E-01f,
    8.92065437225729E-01f,
    8.81105775940274E-01f,
    8.78178064719768E-01f,
    8.81851859443590E-01f
};

const float spectrumCyan[SPECTRUM_SAMPLES] =
{
     1.03716447775989E+00f,
     1.02383033769003E+00f,
     1.02504709160899E+00f,
     1.04889175143971E+00f,
     1.03117530678329E+00f,
     1.05331984065404E+00f,
     1.05358422850977E+00f,
     1.05287714054569E+00f,
     1.05521141254580E+00f,
     8.34460084930349E-01f,
     8.63751701058453E-02f,
    -3.83120210254182E-03f,
    -7.55834633412722E-04f,
     3.90591887740945E-03f,
     1.10204540294205E-02f,
     1.55678459649417E-02f,
};

const float spectrumCyanL[SPECTRUM_SAMPLES] =
{
     1.13006209969381E+00f,
     1.13521116552274E+00f,
     1.13587624097479E+00f,
     1.13634993551468E+00f,
     1.13595840259569E+00f,
     1.13602431314319E+00f,
     1.13586831448230E+00f,
     1.13545913700044E+00f,
     1.12303051839472E+00f,
     7.58797606085962E-01f,
     1.95675861190573E-01f,
    -1.18977125521106E-02f,
    -1.15728871191032E-02f,
    -6.52448006474685E-03f,
    -7.50261793574476E-03f,
    -8.54195338187427E-03f
};

const float spectrumMagenta[SPECTRUM_SAMPLES] =
{
     9.92045376371062E-01f,
     9.89607633429881E-01f,
     1.01826752601052E+00f,
     1.00930398914128E+00f,
     1.01565943248724E+00f,
     3.21410385912808E-01f,
     4.68370100092229E-03f,
    -4.52961460793715E-03f,
     1.64898860075140E-04f,
     4.26725380965491E-01f,
     9.73452739550457E-01f,
     1.00806448675708E+00f,
     8.99801744469785E-01f,
     9.48248373390911E-01f,
     9.29501478474344E-01f,
     8.70087402531841E-01f
};

const float spectrumMagentaL[SPECTRUM_SAMPLES] =
{
     1.04797179134568E+00f,
     1.07649890288995E+00f,
     1.07694669241041E+00f,
     1.07297380716253E+00f,
     1.08321532487253E+00f,
     7.54027321906856E-01f,
     4.21395174789023E-02f,
    -1.71672724818611E-03f,
    -1.36353883682660E-04f,
     1.36648816682865E-01f,
     7.19373119623359E-01f,
     1.07889486960520E+00f,
     1.04197176038030E+00f,
     1.05226411247965E+00f,
     1.02703156525622E+00f,
     1.03925616230766E+00f
};

const float spectrumYellow[SPECTRUM_SAMPLES] =
{
     3.87889564673705E-04f,
    -5.85540221715567E-03f,
    -4.07651153478468E-03f,
     5.64387380150589E-02f,
     2.86932451863357E-01f,
     6.41849110177020E-01f,
     9.84063070662530E-01f,
     1.05129084055994E+00f,
     1.05139640711757E+00f,
     1.05139935594259E+00f,
     1.05141013956755E+00f,
     1.05149897780326E+00f,
     1.05132920978956E+00f,
     1.05088975388065E+00f,
     1.04853824798428E+00f,
     1.04141220527370E+00f
};

const float spectrumYellowL[SPECTRUM_SAMPLES] =
{
     3.37153899782293E-03f,
     1.07957288845707E-04f,
    -1.54162889310590E-04f,
    -1.61216924304805E-04f,
     2.67425018477586E-01f,
     1.03144683664091E+00f,
     1.03664933314566E+00f,
     1.03670116711331E+00f,
     1.03647918231838E+00f,
     1.03662224541084E+00f,
     1.03551581171273E+00f,
     9.23228915197636E-01f,
     6.98062746975481E-01f,
     6.00407382882435E-01f,
     5.79684718025387E-01f,
     5.71448981979936E-01f
};

const float spectrumRed[SPECTRUM_SAMPLES] =
{
     1.42110238349169E-01f,
     1.18897826939937E-01f,
     5.55990190560028E-02f,
     3.62680505442625E-03f,
     9.49781919468718E-03f,
    -3.90042893064980E-03f,
    -6.75471823466475E-03f,
    -9.40645347079313E-03f,
     2.37655363961053E-03f,
     2.99787911396249E-01f,
     9.91116259547556E-01f,
     9.98139449043491E-01f,
     1.00386373217514E+00f,
     9.96042667142156E-01f,
     9.79972039483142E-01f,
     9.61048358866407E-01f
};

const float spectrumRedL[SPECTRUM_SAMPLES] =
{
     5.51601268277975E-02f,
     5.84944112034402E-02f,
     4.20913743517633E-02f,
     1.41612919074148E-02f,
     2.02058095412301E-04f,
    -3.01309552081245E-05f,
    -1.08541818192656E-04f,
    -1.72861199986156E-04f,
     1.33778488315427E-02f,
     2.55685973897239E-01f,
     6.68747787145689E-01f,
     9.27695383249782E-01f,
     9.93884571211217E-01f,
     9.90688216044546E-01f,
     9.82839214970884E-01f,
     9.92900719309551E-01f
};

const float spectrumGreen[SPECTRUM_SAMPLES] =
{
    -1.18404299210650E-03f,
    -1.10013663516642E-02f,
    -1.02215779788221E-02f,
    -8.67575843243223E-03f,
     2.30598683579670E-01f,
     8.58102504950526E-01f,
     9.99237054402251E-01f,
     9.99667295091059E-01f,
     9.99251795619215E-01f,
     7.96029321083520E-01f,
     1.33687749570184E-01f,
    -3.80143563211673E-03f,
    -7.96428029636446E-03f,
    -8.48022681428147E-03f,
    -3.93847449587327E-03f,
     1.32778178417790E-03f
};

const float spectrumGreenL[SPECTRUM_SAMPLES] =
{
     3.22979134624692E-02f,
     6.65902157019276E-03f,
     1.08800226909289E-04f,
    -2.97642840388710E-03f,
     1.63874849158920E-01f,
     1.02471969751034E+00f,
     1.03401271874701E+00f,
     1.02446560834640E+00f,
     1.03663747029238E+00f,
     9.96042758306122E-01f,
    -2.03273309644085E-03f,
     3.70389673008059E-03f,
     1.33698648195478E-02f,
     8.10168987512867E-04f,
     1.89388911083129E-03f,
     3.18200558304089E-02f
};

const float spectrumBlue[SPECTRUM_SAMPLES] =
{
     9.90430987645448E-01f,
     9.95341790487569E-01f,
     9.96036439041839E-01f,
     9.99782996019998E-01f,
     8.87669305997008E-01f,
     4.46078285657302E-01f,
     7.79195074840276E-02f,
    -2.14533954386087E-04f,
     6.63978441316659E-04f,
     1.62445063434862E-03f,
     3.77186675598739E-03f,
     3.19820136565273E-02f,
     4.95427893490668E-02f,
     4.48278652853951E-02f,
     2.58720398512374E-02f,
     5.56650907176684E-03f
};

const float spectrumBlueL[SPECTRUM_SAMPLES] =
{
     1.05544788360900E+00f,
     1.05404510064212E+00f,
     1.05791850456362E+00f,
     1.05814226651589E+00f,
     1.05666417595024E+00f,
     6.84305181257886E-01f,
    -1.61074247897293E-03f,
    -1.36605267636382E-03f,
    -3.30296431807605E-04f,
    -1.45626164107289E-03f,
    -1.49959410071174E-03f,
     2.08006611608046E-02f,
     1.13755048642056E-01f,
     1.52067723550880E-01f,
     1.68109346820554E-01f,
     1.74194172606676E-01f
};

#else

const float X[SPECTRUM_SAMPLES] =
{
    0.704719194064694f,
    2.45612825752715f,
    8.05919368162368f,
    16.3991923955296f,
    26.0397303584315f,
    29.3129037088222f,
    26.3344474095872f,
    17.8405649537739f,
    9.09217349249588f,
    2.94265977310254f,
    0.468913675410046f,
    0.898296138990984f,
    6.14434813643801f,
    16.8954464697615f,
    29.2570087297861f,
    44.3477175902877f,
    59.45f,
    74.4860262967351f,
    90.6445191071685f,
    95.9706456420296f,
    103.784866140455f,
    99.5521507183938f,
    84.6507668018606f,
    61.5120323038324f,
    44.2958425675426f,
    27.1334189988948f,
    16.1994298557152f,
    9.00732538761708f,
    4.63907953796373f,
    1.98461278785078f,
    1.04114730065218
};

const float Y[SPECTRUM_SAMPLES] =
{
    0.0195016632319789f,
    0.068304187350215f,
    0.239892653121705f,
    0.670062105629249f,
    1.71963304882257f,
    3.31317769463189f,
    5.43351734723257f,
    8.30842853959023f,
    13.2161643551524f,
    19.1231517026176f,
    30.9100239096826f,
    48.5852642916629f,
    68.950326803714f,
    87.9992438485462f,
    96.1129005792559f,
    101.796692192635f,
    99.5f,
    93.0464467058022f,
    86.0643147694386f,
    70.7880529582153f,
    61.6534085244091f,
    49.9448751359985f,
    37.7458551420146f,
    25.3746708600803f,
    17.3069266562178f,
    10.2408318620167f,
    5.99251195390313f,
    3.29787657212525f,
    1.6862166377033f,
    0.71778286291872f,
    0.37597729297547f
};

const float Z[SPECTRUM_SAMPLES] =
{
    3.34138395279395f,
    11.7076764102765f,
    38.7186742138432f,
    80.0377632379214f,
    130.621831055477f,
    154.508298011424f,
    151.16045260001f,
    117.58919460011f,
    77.2844348592836f,
    42.7637136286111f,
    26.0294938186801f,
    15.2806934611155f,
    7.59910194772867f,
    4.30400013997066f,
    2.0451696873783f,
    0.895241836639712f,
    0.39f,
    0.205249514792211f,
    0.163225523487228f,
    0.102862428340868f,
    0.0781659696030543f,
    0.0337599553603171f,
    0.0188233923280388f,
    0.00478767278965021f,
    0.00197793447499632f,
    0.f,
    0.f,
    0.f,
    0.f,
    0.f,
    0.f
};

constexpr const float INVY_SUM = 1.f/1050.2020328567f;

const float spectrumWhite[SPECTRUM_SAMPLES] =
{
    1.0618958571272863f,   1.0615019980348779f,
    1.0614335379927147f,   1.0622711654692485f,
    1.0622036218416742f,   1.0625059965187085f,
    1.0623938486985884f,   1.0624706448043137f,
    1.0625048144827762f,   1.0624366131308856f,
    1.0620694238892607f,   1.0613167586932164f,
    1.0610334029377020f,   1.0613868564828413f,
    1.0614215366116762f,   1.0620336151299086f,
    1.0625497454805051f,   1.0624317487992085f,
    1.0625249140554480f,   1.0624277664486914f,
    1.0624749854090769f,   1.0625538581025402f,
    1.0625326910104864f,   1.0623922312225325f,
    1.0623650980354129f,   1.0625256476715284f,
    1.0612277619533155f,   1.0594262608698046f,
    1.0599810758292072f,   1.0602547314449409f,
    1.0601263046243634f,
};

const float spectrumWhiteL[SPECTRUM_SAMPLES] =
{
    1.1565232050369776E+00f,   1.1567225000119139E+00f,
    1.1566203150243823E+00f,   1.1555782088080084E+00f,
    1.1562175509215700E+00f,   1.1567674012207332E+00f,
    1.1568023194808630E+00f,   1.1567677445485520E+00f,
    1.1563563182952830E+00f,   1.1567054702510189E+00f,
    1.1565134139372772E+00f,   1.1564336176499312E+00f,
    1.1568023181530034E+00f,   1.1473147688514642E+00f,
    1.1339317140561065E+00f,   1.1293876490671435E+00f,
    1.1290515328639648E+00f,   1.0504864823782283E+00f,
    1.0459696042230884E+00f,   9.9366687168595691E-01f,
    9.5601669265393940E-01f,   9.2467482033511805E-01f,
    9.1499944702051761E-01f,   8.9939467658453465E-01f,
    8.9542520751331112E-01f,   8.8870566693814745E-01f,
    8.8222843814228114E-01f,   8.7998311373826676E-01f,
    8.7635244612244578E-01f,   8.8000368331709111E-01f,
    8.8065665428441120E-01f,
};

const float spectrumCyan[SPECTRUM_SAMPLES] =
{
     1.0414628021426751E+00f,   1.0328661533771188E+00f,
     1.0126146228964314E+00f,   1.0350460524836209E+00f,
     1.0078661447098567E+00f,   1.0422280385081280E+00f,
     1.0442596738499825E+00f,   1.0535238290294409E+00f,
     1.0180776226938120E+00f,   1.0442729908727713E+00f,
     1.0529362541920750E+00f,   1.0537034271160244E+00f,
     1.0533901869215969E+00f,   1.0537782700979574E+00f,
     1.0527093770467102E+00f,   1.0530449040446797E+00f,
     1.0550554640191208E+00f,   1.0553673610724821E+00f,
     1.0454306634683976E+00f,   6.2348950639230805E-01f,
     1.8038071613188977E-01f,  -7.6303759201984539E-03f,
    -1.5217847035781367E-04f,  -7.5102257347258311E-03f,
    -2.1708639328491472E-03f,   6.5919466602369636E-04f,
     1.2278815318539780E-02f,  -4.4669775637208031E-03f,
     1.7119799082865147E-02f,   4.9211089759759801E-03f,
     5.8762925143334985E-03f,
};

const float spectrumCyanL[SPECTRUM_SAMPLES] =
{
     1.1334479663682135E+00f,   1.1266762330194116E+00f,
     1.1346827504710164E+00f,   1.1357395805744794E+00f,
     1.1356371830149636E+00f,   1.1361152989346193E+00f,
     1.1362179057706772E+00f,   1.1364819652587022E+00f,
     1.1355107110714324E+00f,   1.1364060941199556E+00f,
     1.1360363621722465E+00f,   1.1360122641141395E+00f,
     1.1354266882467030E+00f,   1.1363099407179136E+00f,
     1.1355450412632506E+00f,   1.1353732327376378E+00f,
     1.1349496420726002E+00f,   1.1111113947168556E+00f,
     9.0598740429727143E-01f,   6.1160780787465330E-01f,
     2.9539752170999634E-01f,   9.5954200671150097E-02f,
    -1.1650792030826267E-02f,  -1.2144633073395025E-02f,
    -1.1148167569748318E-02f,  -1.1997606668458151E-02f,
    -5.0506855475394852E-03f,  -7.9982745819542154E-03f,
    -9.4722817708236418E-03f,  -5.5329541006658815E-03f,
    -4.5428914028274488E-03f,
};

const float spectrumMagenta[SPECTRUM_SAMPLES] =
{
     9.9422138151236850E-01f,   9.8986937122975682E-01f,
     9.8293658286116958E-01f,   9.9627868399859310E-01f,
     1.0198955019000133E+00f,   1.0166395501210359E+00f,
     1.0220913178757398E+00f,   9.9651666040682441E-01f,
     1.0097766178917882E+00f,   1.0215422470827016E+00f,
     6.4031953387790963E-01f,   2.5012379477078184E-03f,
     6.5339939555769944E-03f,   2.8334080462675826E-03f,
    -5.1209675389074505E-11f,  -9.0592291646646381E-03f,
     3.3936718323331200E-03f,  -3.0638741121828406E-03f,
     2.2203936168286292E-01f,   6.3141140024811970E-01f,
     9.7480985576500956E-01f,   9.7209562333590571E-01f,
     1.0173770302868150E+00f,   9.9875194322734129E-01f,
     9.4701725739602238E-01f,   8.5258623154354796E-01f,
     9.4897798581660842E-01f,   9.4751876096521492E-01f,
     9.9598944191059791E-01f,   8.6301351503809076E-01f,
     8.9150987853523145E-01f,
};

const float spectrumMagentaL[SPECTRUM_SAMPLES] =
{
     1.0371892935878366e+00f,   1.0587542891035364e+00f,
     1.0767271213688903e+00f,   1.0762706844110288e+00f,
     1.0795289105258212e+00f,   1.0743644742950074e+00f,
     1.0727028691194342e+00f,   1.0732447452056488e+00f,
     1.0823760816041414e+00f,   1.0840545681409282e+00f,
     9.5607567526306658e-01f,   5.5197896855064665e-01f,
     8.4191094887247575e-02f,   8.7940070557041006e-05f,
    -2.3086408335071251e-03f,  -1.1248136628651192e-03f,
    -7.7297612754989586e-11f,  -2.7270769006770834e-04f,
     1.4466473094035592e-02f,   2.5883116027169478e-01f,
     5.2907999827566732e-01f,   9.0966624097105164e-01f,
     1.0690571327307956e+00f,   1.0887326064796272e+00f,
     1.0637622289511852e+00f,   1.0201812918094260e+00f,
     1.0262196688979945e+00f,   1.0783085560613190e+00f,
     9.8333849623218872e-01f,   1.0707246342802621e+00f,
     1.0634247770423768e+00f,
};

const float spectrumYellow[SPECTRUM_SAMPLES] =
{
     5.5740622924920873E-03f,  -4.7982831631446787E-03f,
    -5.2536564298613798E-03f,  -6.4571480044499710E-03f,
    -5.9693514658007013E-03f,  -2.1836716037686721E-03f,
     1.6781120601055327E-02f,   9.6096355429062641E-02f,
     2.1217357081986446E-01f,   3.6169133290685068E-01f,
     5.3961011543232529E-01f,   7.4408810492171507E-01f,
     9.2209571148394054E-01f,   1.0460304298411225E+00f,
     1.0513824989063714E+00f,   1.0511991822135085E+00f,
     1.0510530911991052E+00f,   1.0517397230360510E+00f,
     1.0516043086790485E+00f,   1.0511944032061460E+00f,
     1.0511590325868068E+00f,   1.0516612465483031E+00f,
     1.0514038526836869E+00f,   1.0515941029228475E+00f,
     1.0511460436960840E+00f,   1.0515123758830476E+00f,
     1.0508871369510702E+00f,   1.0508923708102380E+00f,
     1.0477492815668303E+00f,   1.0493272144017338E+00f,
     1.0435963333422726E+00f,
};

const float spectrumYellowL[SPECTRUM_SAMPLES] =
{
     2.7756958965811972E-03f,   3.9673820990646612E-03f,
    -1.4606936788606750E-04f,   3.6198394557748065E-04f,
    -2.5819258699309733E-04f,  -5.0133191628082274E-05f,
    -2.4437242866157116E-04f,  -7.8061419948038946E-05f,
     4.9690301207540921E-02f,   4.8515973574763166E-01f,
     1.0295725854360589E+00f,   1.0333210878457741E+00f,
     1.0368102644026933E+00f,   1.0364884018886333E+00f,
     1.0365427939411784E+00f,   1.0368595402854539E+00f,
     1.0365645405660555E+00f,   1.0363938240707142E+00f,
     1.0367205578770746E+00f,   1.0365239329446050E+00f,
     1.0361531226427443E+00f,   1.0348785007827348E+00f,
     1.0042729660717318E+00f,   8.4218486432354278E-01f,
     7.3759394894801567E-01f,   6.5853154500294642E-01f,
     6.0531682444066282E-01f,   5.9549794132420741E-01f,
     5.9419261278443136E-01f,   5.6517682326634266E-01f,
     5.6061186014968556E-01f,
};

const float spectrumRed[SPECTRUM_SAMPLES] =
{
     1.6575604867086180E-01f,   1.1846442802747797E-01f,
     1.2408293329637447E-01f,   1.1371272058349924E-01f,
     7.8992434518899132E-02f,   3.2205603593106549E-02f,
    -1.0798365407877875E-02f,   1.8051975516730392E-02f,
     5.3407196598730527E-03f,   1.3654918729501336E-02f,
    -5.9564213545642841E-03f,  -1.8444365067353252E-03f,
    -1.0571884361529504E-02f,  -2.9375521078000011E-03f,
    -1.0790476271835936E-02f,  -8.0224306697503633E-03f,
    -2.2669167702495940E-03f,   7.0200240494706634E-03f,
    -8.1528469000299308E-03f,   6.0772866969252792E-01f,
     9.8831560865432400E-01f,   9.9391691044078823E-01f,
     1.0039338994753197E+00f,   9.9234499861167125E-01f,
     9.9926530858855522E-01f,   1.0084621557617270E+00f,
     9.8358296827441216E-01f,   1.0085023660099048E+00f,
     9.7451138326568698E-01f,   9.8543269570059944E-01f,
     9.3495763980962043E-01f,
};

const float spectrumRedL[SPECTRUM_SAMPLES] =
{
     5.4711187157291841E-02f,   5.5609066498303397E-02f,
     6.0755873790918236E-02f,   5.6232948615962369E-02f,
     4.6169940535708678E-02f,   3.8012808167818095E-02f,
     2.4424225756670338E-02f,   3.8983580581592181E-03f,
    -5.6082252172734437E-04f,   9.6493871255194652E-04f,
     3.7341198051510371E-04f,  -4.3367389093135200E-04f,
    -9.3533962256892034E-05f,  -1.2354967412842033E-04f,
    -1.4524548081687461E-04f,  -2.0047691915543731E-04f,
    -4.9938587694693670E-04f,   2.7255083540032476E-02f,
     1.6067405906297061E-01f,   3.5069788873150953E-01f,
     5.7357465538418961E-01f,   7.6392091890718949E-01f,
     8.9144466740381523E-01f,   9.6394609909574891E-01f,
     9.8879464276016282E-01f,   9.9897449966227203E-01f,
     9.8605140403564162E-01f,   9.9532502805345202E-01f,
     9.7433478377305371E-01f,   9.9134364616871407E-01f,
     9.8866287772174755E-01f,
};

const float spectrumGreen[SPECTRUM_SAMPLES] =
{
     2.6494153587602255E-03f,  -5.0175013429732242E-03f,
    -1.2547236272489583E-02f,  -9.4554964308388671E-03f,
    -1.2526086181600525E-02f,  -7.9170697760437767E-03f,
    -7.9955735204175690E-03f,  -9.3559433444469070E-03f,
     6.5468611982999303E-02f,   3.9572875517634137E-01f,
     7.5244022299886659E-01f,   9.6376478690218559E-01f,
     9.9854433855162328E-01f,   9.9992977025287921E-01f,
     9.9939086751140449E-01f,   9.9994372267071396E-01f,
     9.9939121813418674E-01f,   9.9911237310424483E-01f,
     9.6019584878271580E-01f,   6.3186279338432438E-01f,
     2.5797401028763473E-01f,   9.4014888527335638E-03f,
    -3.0798345608649747E-03f,  -4.5230367033685034E-03f,
    -6.8933410388274038E-03f,  -9.0352195539015398E-03f,
    -8.5913667165340209E-03f,  -8.3690869120289398E-03f,
    -7.8685832338754313E-03f,  -8.3657578711085132E-06f,
     5.4301225442817177E-03f,
};

const float spectrumGreenL[SPECTRUM_SAMPLES] =
{
     2.5168388755514630E-02f,   3.9427438169423720E-02f,
     6.2059571596425793E-03f,   7.1120859807429554E-03f,
     2.1760044649139429E-04f,   7.3271839984290210E-12f,
    -2.1623066217181700E-02f,   1.5670209409407512E-02f,
     2.8019603188636222E-03f,   3.2494773799897647E-01f,
     1.0164917292316602E+00f,   1.0329476657890369E+00f,
     1.0321586962991549E+00f,   1.0358667411948619E+00f,
     1.0151235476834941E+00f,   1.0338076690093119E+00f,
     1.0371372378155013E+00f,   1.0361377027692558E+00f,
     1.0229822432557210E+00f,   9.6910327335652324E-01f,
    -5.1785923899878572E-03f,   1.1131261971061429E-03f,
     6.6675503033011771E-03f,   7.4024315686001957E-04f,
     2.1591567633473925E-02f,   5.1481620056217231E-03f,
     1.4561928645728216E-03f,   1.6414511045291513E-04f,
    -6.4630764968453287E-03f,   1.0250854718507939E-02f,
     4.2387394733956134E-02f,
};

const float spectrumBlue[SPECTRUM_SAMPLES] =
{
     9.9209771469720676E-01f,   9.8876426059369127E-01f,
     9.9539040744505636E-01f,   9.9529317353008218E-01f,
     9.9181447411633950E-01f,   1.0002584039673432E+00f,
     9.9968478437342512E-01f,   9.9988120766657174E-01f,
     9.8504012146370434E-01f,   7.9029849053031276E-01f,
     5.6082198617463974E-01f,   3.3133458513996528E-01f,
     1.3692410840839175E-01f,   1.8914906559664151E-02f,
    -5.1129770932550889E-06f,  -4.2395493167891873E-04f,
    -4.1934593101534273E-04f,   1.7473028136486615E-03f,
     3.7999160177631316E-03f,  -5.5101474906588642E-04f,
    -4.3716662898480967E-05f,   7.5874501748732798E-03f,
     2.5795650780554021E-02f,   3.8168376532500548E-02f,
     4.9489586408030833E-02f,   4.9595992290102905E-02f,
     4.9814819505812249E-02f,   3.9840911064978023E-02f,
     3.0501024937233868E-02f,   2.1243054765241080E-02f,
     6.9596532104356399E-03f,
};

const float spectrumBlueL[SPECTRUM_SAMPLES] =
{
     1.0570490759328752E+00f,   1.0538466912851301E+00f,
     1.0550494258140670E+00f,   1.0530407754701832E+00f,
     1.0579930596460185E+00f,   1.0578439494812371E+00f,
     1.0583132387180239E+00f,   1.0579712943137616E+00f,
     1.0561884233578465E+00f,   1.0571399285426490E+00f,
     1.0425795187752152E+00f,   3.2603084374056102E-01f,
    -1.9255628442412243E-03f,  -1.2959221137046478E-03f,
    -1.4357356276938696E-03f,  -1.2963697250337886E-03f,
    -1.9227081162373899E-03f,   1.2621152526221778E-03f,
    -1.6095249003578276E-03f,  -1.3029983817879568E-03f,
    -1.7666600873954916E-03f,  -1.2325281140280050E-03f,
     1.0316809673254932E-02f,   3.1284512648354357E-02f,
     8.8773879881746481E-02f,   1.3873621740236541E-01f,
     1.5535067531939065E-01f,   1.4878477178237029E-01f,
     1.6624255403475907E-01f,   1.6997613960634927E-01f,
     1.5769743995852967E-01f,
};

#endif

//More memory usage but I avoid to construct and destroy these multiple times
//while parsing RGB values
const Spectrum SPECTRUM_WHITE(spectrumWhite);
const Spectrum SPECTRUM_WHITEL(spectrumWhiteL);
const Spectrum SPECTRUM_CYAN(spectrumCyan);
const Spectrum SPECTRUM_CYANL(spectrumCyanL);
const Spectrum SPECTRUM_MAGENTA(spectrumMagenta);
const Spectrum SPECTRUM_MAGENTAL(spectrumMagentaL);
const Spectrum SPECTRUM_YELLOW(spectrumYellow);
const Spectrum SPECTRUM_YELLOWL(spectrumYellowL);
const Spectrum SPECTRUM_RED(spectrumRed);
const Spectrum SPECTRUM_REDL(spectrumRedL);
const Spectrum SPECTRUM_GREEN(spectrumGreen);
const Spectrum SPECTRUM_GREENL(spectrumGreenL);
const Spectrum SPECTRUM_BLUE(spectrumBlue);
const Spectrum SPECTRUM_BLUEL(spectrumBlueL);
const Spectrum SPECTRUM_BLACK(0);

Spectrum::Spectrum()
{
    //do nothing. Too expensive to initialize if I need to assign it later
}

Spectrum::Spectrum(int)
{
    memset(Spectrum::w,0,sizeof(float)*SPECTRUM_SAMPLES);
}

Spectrum::Spectrum(const float* vals)
{
    for(int i=0;i<SPECTRUM_SAMPLES;i++)
        Spectrum::w[i] = vals[i];
}

Spectrum::Spectrum(ColorRGB c, bool l)
{
    memset(Spectrum::w,0,sizeof(float)*SPECTRUM_SAMPLES);
    if(!l)
    {
        if(c.r<c.g && c.r<c.b)
        {
            *this += SPECTRUM_WHITE*c.r;
            if(c.g <= c.b)
            {
                *this += SPECTRUM_CYAN*(c.g-c.r);
                *this += SPECTRUM_BLUE*(c.b-c.g);
            }
            else
            {
                *this += SPECTRUM_CYAN*(c.b-c.r);
                *this += SPECTRUM_GREEN*(c.g-c.b);
            }
        }
        else if(c.g<=c.r && c.g<=c.b)
        {
            *this += SPECTRUM_WHITE*c.g;
            if(c.r <= c.b)
            {
                *this += SPECTRUM_MAGENTA*(c.r-c.g);
                *this += SPECTRUM_BLUE*(c.b-c.r);
            }
            else
            {
                *this += SPECTRUM_MAGENTA*(c.r-c.g);
                *this += SPECTRUM_RED*(c.r-c.b);
            }
        }
        else
        {
            *this += SPECTRUM_WHITE*c.b;
            if(c.r <= c.g)
            {
                *this += SPECTRUM_YELLOW*(c.r-c.b);
                *this += SPECTRUM_GREEN*(c.g-c.r);
            }
            else
            {
                *this += SPECTRUM_YELLOW*(c.g-c.b);
                *this += SPECTRUM_RED*(c.r-c.g);
            }
        }
        *this *= 0.94f;
    }
    else
    {
        if(c.r<c.g && c.r<c.b)
        {
            *this += SPECTRUM_WHITEL*c.r;
            if(c.g <= c.b)
            {
                *this += SPECTRUM_CYANL*(c.g-c.r);
                *this += SPECTRUM_BLUEL*(c.b-c.g);
            }
            else
            {
                *this += SPECTRUM_CYANL*(c.b-c.r);
                *this += SPECTRUM_GREENL*(c.g-c.b);
            }
        }
        else if(c.g<=c.r && c.g<=c.b)
        {
            *this += SPECTRUM_WHITEL*c.g;
            if(c.r <= c.b)
            {
                *this += SPECTRUM_MAGENTAL*(c.r-c.g);
                *this += SPECTRUM_BLUEL*(c.b-c.r);
            }
            else
            {
                *this += SPECTRUM_MAGENTAL*(c.r-c.g);
                *this += SPECTRUM_REDL*(c.r-c.b);
            }
        }
        else
        {
            *this += SPECTRUM_WHITEL*c.b;
            if(c.r <= c.g)
            {
                *this += SPECTRUM_YELLOWL*(c.r-c.b);
                *this += SPECTRUM_GREENL*(c.g-c.r);
            }
            else
            {
                *this += SPECTRUM_YELLOWL*(c.g-c.b);
                *this += SPECTRUM_REDL*(c.r-c.g);
            }
        }
        *this *= 0.86445f;
    }
    for(int i=0;i<SPECTRUM_SAMPLES;i++)
        w[i] = w[i]<0.f?0.f:w[i]>1.f?1.f:w[i];
}

ColorXYZ Spectrum::toXYZ()const
{
    float x = 0;
    float y = 0;
    float z = 0;
    x+=Spectrum::w[0]*X[0];
    x+=Spectrum::w[1]*X[1];
    x+=Spectrum::w[2]*X[2];
    x+=Spectrum::w[3]*X[3];
    x+=Spectrum::w[4]*X[4];
    x+=Spectrum::w[5]*X[5];
    x+=Spectrum::w[6]*X[6];
    x+=Spectrum::w[7]*X[7];
    x+=Spectrum::w[8]*X[8];
    x+=Spectrum::w[9]*X[9];
    x+=Spectrum::w[10]*X[10];
    x+=Spectrum::w[11]*X[11];
    x+=Spectrum::w[12]*X[12];
    x+=Spectrum::w[13]*X[13];
    x+=Spectrum::w[14]*X[14];
    x+=Spectrum::w[15]*X[15];
    
    y+=Spectrum::w[0]*Y[0];
    y+=Spectrum::w[1]*Y[1];
    y+=Spectrum::w[2]*Y[2];
    y+=Spectrum::w[3]*Y[3];
    y+=Spectrum::w[4]*Y[4];
    y+=Spectrum::w[5]*Y[5];
    y+=Spectrum::w[6]*Y[6];
    y+=Spectrum::w[7]*Y[7];
    y+=Spectrum::w[8]*Y[8];
    y+=Spectrum::w[9]*Y[9];
    y+=Spectrum::w[10]*Y[10];
    y+=Spectrum::w[11]*Y[11];
    y+=Spectrum::w[12]*Y[12];
    y+=Spectrum::w[13]*Y[13];
    y+=Spectrum::w[14]*Y[14];
    y+=Spectrum::w[15]*Y[15];
    
    z+=Spectrum::w[0]*Z[0];
    z+=Spectrum::w[1]*Z[1];
    z+=Spectrum::w[2]*Z[2];
    z+=Spectrum::w[3]*Z[3];
    z+=Spectrum::w[4]*Z[4];
    z+=Spectrum::w[5]*Z[5];
    z+=Spectrum::w[6]*Z[6];
    z+=Spectrum::w[7]*Z[7];
    z+=Spectrum::w[8]*Z[8];
    z+=Spectrum::w[9]*Z[9];
    z+=Spectrum::w[10]*Z[10];
    z+=Spectrum::w[11]*Z[11];
    z+=Spectrum::w[12]*Z[12];
    z+=Spectrum::w[13]*Z[13];
    z+=Spectrum::w[14]*Z[14];
    z+=Spectrum::w[15]*Z[15];
#if HQ_SPECTRUM!=0
    x+=Spectrum::w[16]*X[16];
    x+=Spectrum::w[17]*X[17];
    x+=Spectrum::w[18]*X[18];
    x+=Spectrum::w[19]*X[19];
    x+=Spectrum::w[20]*X[20];
    x+=Spectrum::w[21]*X[21];
    x+=Spectrum::w[22]*X[22];
    x+=Spectrum::w[23]*X[23];
    x+=Spectrum::w[24]*X[24];
    x+=Spectrum::w[25]*X[25];
    x+=Spectrum::w[26]*X[26];
    x+=Spectrum::w[27]*X[27];
    x+=Spectrum::w[28]*X[28];
    x+=Spectrum::w[29]*X[29];
    x+=Spectrum::w[30]*X[30];
    y+=Spectrum::w[16]*Y[16];
    y+=Spectrum::w[17]*Y[17];
    y+=Spectrum::w[18]*Y[18];
    y+=Spectrum::w[19]*Y[19];
    y+=Spectrum::w[20]*Y[20];
    y+=Spectrum::w[21]*Y[21];
    y+=Spectrum::w[22]*Y[22];
    y+=Spectrum::w[23]*Y[23];
    y+=Spectrum::w[24]*Y[24];
    y+=Spectrum::w[25]*Y[25];
    y+=Spectrum::w[26]*Y[26];
    y+=Spectrum::w[27]*Y[27];
    y+=Spectrum::w[28]*Y[28];
    y+=Spectrum::w[29]*Y[29];
    y+=Spectrum::w[30]*Y[30];
    z+=Spectrum::w[16]*Z[16];
    z+=Spectrum::w[17]*Z[17];
    z+=Spectrum::w[18]*Z[18];
    z+=Spectrum::w[19]*Z[19];
    z+=Spectrum::w[20]*Z[20];
    z+=Spectrum::w[21]*Z[21];
    z+=Spectrum::w[22]*Z[22];
    z+=Spectrum::w[23]*Z[23];
    z+=Spectrum::w[24]*Z[24];
    z+=Spectrum::w[25]*Z[25];
    z+=Spectrum::w[26]*Z[26];
    z+=Spectrum::w[27]*Z[27];
    z+=Spectrum::w[28]*Z[28];
    z+=Spectrum::w[29]*Z[29];
    z+=Spectrum::w[30]*Z[30];
#endif
    x*=INVY_SUM;
    y*=INVY_SUM;
    z*=INVY_SUM;
    
    return ColorXYZ(x,y,z);
}

float Spectrum::luminance()const
{
    float y = 0;
    y+=Spectrum::w[0]*Y[0];
    y+=Spectrum::w[1]*Y[1];
    y+=Spectrum::w[2]*Y[2];
    y+=Spectrum::w[3]*Y[3];
    y+=Spectrum::w[4]*Y[4];
    y+=Spectrum::w[5]*Y[5];
    y+=Spectrum::w[6]*Y[6];
    y+=Spectrum::w[7]*Y[7];
    y+=Spectrum::w[8]*Y[8];
    y+=Spectrum::w[9]*Y[9];
    y+=Spectrum::w[10]*Y[10];
    y+=Spectrum::w[11]*Y[11];
    y+=Spectrum::w[12]*Y[12];
    y+=Spectrum::w[13]*Y[13];
    y+=Spectrum::w[14]*Y[14];
    y+=Spectrum::w[15]*Y[15];
#if HQ_SPECTRUM!=0
    y+=Spectrum::w[16]*Y[16];
    y+=Spectrum::w[17]*Y[17];
    y+=Spectrum::w[18]*Y[18];
    y+=Spectrum::w[19]*Y[19];
    y+=Spectrum::w[20]*Y[20];
    y+=Spectrum::w[21]*Y[21];
    y+=Spectrum::w[22]*Y[22];
    y+=Spectrum::w[23]*Y[23];
    y+=Spectrum::w[24]*Y[24];
    y+=Spectrum::w[25]*Y[25];
    y+=Spectrum::w[26]*Y[26];
    y+=Spectrum::w[27]*Y[27];
    y+=Spectrum::w[28]*Y[28];
    y+=Spectrum::w[29]*Y[29];
    y+=Spectrum::w[30]*Y[30];
#endif
    
    return y*INVY_SUM;
}

bool Spectrum::isBlack()const
{
    for(int i=0;i<SPECTRUM_SAMPLES;i++)
        if(Spectrum::w[i]!=0)
            return false;
    return true;
}

Spectrum Spectrum::operator+(const Spectrum& s)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] + s.w[0];
    retval.w[1] = Spectrum::w[1] + s.w[1];
    retval.w[2] = Spectrum::w[2] + s.w[2];
    retval.w[3] = Spectrum::w[3] + s.w[3];
    retval.w[4] = Spectrum::w[4] + s.w[4];
    retval.w[5] = Spectrum::w[5] + s.w[5];
    retval.w[6] = Spectrum::w[6] + s.w[6];
    retval.w[7] = Spectrum::w[7] + s.w[7];
    retval.w[8] = Spectrum::w[8] + s.w[8];
    retval.w[9] = Spectrum::w[9] + s.w[9];
    retval.w[10] = Spectrum::w[10] + s.w[10];
    retval.w[11] = Spectrum::w[11] + s.w[11];
    retval.w[12] = Spectrum::w[12] + s.w[12];
    retval.w[13] = Spectrum::w[13] + s.w[13];
    retval.w[14] = Spectrum::w[14] + s.w[14];
    retval.w[15] = Spectrum::w[15] + s.w[15];
#if HQ_SPECTRUM!=0
    retval.w[16] = Spectrum::w[16] + s.w[16];
    retval.w[17] = Spectrum::w[17] + s.w[17];
    retval.w[18] = Spectrum::w[18] + s.w[18];
    retval.w[19] = Spectrum::w[19] + s.w[19];
    retval.w[20] = Spectrum::w[20] + s.w[20];
    retval.w[21] = Spectrum::w[21] + s.w[21];
    retval.w[22] = Spectrum::w[22] + s.w[22];
    retval.w[23] = Spectrum::w[23] + s.w[23];
    retval.w[24] = Spectrum::w[24] + s.w[24];
    retval.w[25] = Spectrum::w[25] + s.w[25];
    retval.w[26] = Spectrum::w[26] + s.w[26];
    retval.w[27] = Spectrum::w[27] + s.w[27];
    retval.w[28] = Spectrum::w[28] + s.w[28];
    retval.w[29] = Spectrum::w[29] + s.w[29];
    retval.w[30] = Spectrum::w[30] + s.w[30];
#endif
    return retval;
}

void Spectrum::operator+=(const Spectrum& s)
{
    Spectrum::w[0] += s.w[0];
    Spectrum::w[1] += s.w[1];
    Spectrum::w[2] += s.w[2];
    Spectrum::w[3] += s.w[3];
    Spectrum::w[4] += s.w[4];
    Spectrum::w[5] += s.w[5];
    Spectrum::w[6] += s.w[6];
    Spectrum::w[7] += s.w[7];
    Spectrum::w[8] += s.w[8];
    Spectrum::w[9] += s.w[9];
    Spectrum::w[10] += s.w[10];
    Spectrum::w[11] += s.w[11];
    Spectrum::w[12] += s.w[12];
    Spectrum::w[13] += s.w[13];
    Spectrum::w[14] += s.w[14];
    Spectrum::w[15] += s.w[15];
#if HQ_SPECTRUM!=0
    Spectrum::w[16] += s.w[16];
    Spectrum::w[17] += s.w[17];
    Spectrum::w[18] += s.w[18];
    Spectrum::w[19] += s.w[19];
    Spectrum::w[20] += s.w[20];
    Spectrum::w[21] += s.w[21];
    Spectrum::w[22] += s.w[22];
    Spectrum::w[23] += s.w[23];
    Spectrum::w[24] += s.w[24];
    Spectrum::w[25] += s.w[25];
    Spectrum::w[26] += s.w[26];
    Spectrum::w[27] += s.w[27];
    Spectrum::w[28] += s.w[28];
    Spectrum::w[29] += s.w[29];
    Spectrum::w[30] += s.w[30];
#endif
}

Spectrum Spectrum::operator-(const Spectrum& s)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] - s.w[0];
    retval.w[1] = Spectrum::w[1] - s.w[1];
    retval.w[2] = Spectrum::w[2] - s.w[2];
    retval.w[3] = Spectrum::w[3] - s.w[3];
    retval.w[4] = Spectrum::w[4] - s.w[4];
    retval.w[5] = Spectrum::w[5] - s.w[5];
    retval.w[6] = Spectrum::w[6] - s.w[6];
    retval.w[7] = Spectrum::w[7] - s.w[7];
    retval.w[8] = Spectrum::w[8] - s.w[8];
    retval.w[9] = Spectrum::w[9] - s.w[9];
    retval.w[10] = Spectrum::w[10] - s.w[10];
    retval.w[11] = Spectrum::w[11] - s.w[11];
    retval.w[12] = Spectrum::w[12] - s.w[12];
    retval.w[13] = Spectrum::w[13] - s.w[13];
    retval.w[14] = Spectrum::w[14] - s.w[14];
    retval.w[15] = Spectrum::w[15] - s.w[15];
#if HQ_SPECTRUM!=0
    retval.w[16] = Spectrum::w[16] - s.w[16];
    retval.w[17] = Spectrum::w[17] - s.w[17];
    retval.w[18] = Spectrum::w[18] - s.w[18];
    retval.w[19] = Spectrum::w[19] - s.w[19];
    retval.w[20] = Spectrum::w[20] - s.w[20];
    retval.w[21] = Spectrum::w[21] - s.w[21];
    retval.w[22] = Spectrum::w[22] - s.w[22];
    retval.w[23] = Spectrum::w[23] - s.w[23];
    retval.w[24] = Spectrum::w[24] - s.w[24];
    retval.w[25] = Spectrum::w[25] - s.w[25];
    retval.w[26] = Spectrum::w[26] - s.w[26];
    retval.w[27] = Spectrum::w[27] - s.w[27];
    retval.w[28] = Spectrum::w[28] - s.w[28];
    retval.w[29] = Spectrum::w[29] - s.w[29];
    retval.w[30] = Spectrum::w[30] - s.w[30];
#endif
    return retval;

}

void Spectrum::operator-=(const Spectrum& s)
{
    Spectrum::w[0] -= s.w[0];
    Spectrum::w[1] -= s.w[1];
    Spectrum::w[2] -= s.w[2];
    Spectrum::w[3] -= s.w[3];
    Spectrum::w[4] -= s.w[4];
    Spectrum::w[5] -= s.w[5];
    Spectrum::w[6] -= s.w[6];
    Spectrum::w[7] -= s.w[7];
    Spectrum::w[8] -= s.w[8];
    Spectrum::w[9] -= s.w[9];
    Spectrum::w[10] -= s.w[10];
    Spectrum::w[11] -= s.w[11];
    Spectrum::w[12] -= s.w[12];
    Spectrum::w[13] -= s.w[13];
    Spectrum::w[14] -= s.w[14];
    Spectrum::w[15] -= s.w[15];
#if HQ_SPECTRUM!=0
    Spectrum::w[16] -= s.w[16];
    Spectrum::w[17] -= s.w[17];
    Spectrum::w[18] -= s.w[18];
    Spectrum::w[19] -= s.w[19];
    Spectrum::w[20] -= s.w[20];
    Spectrum::w[21] -= s.w[21];
    Spectrum::w[22] -= s.w[22];
    Spectrum::w[23] -= s.w[23];
    Spectrum::w[24] -= s.w[24];
    Spectrum::w[25] -= s.w[25];
    Spectrum::w[26] -= s.w[26];
    Spectrum::w[27] -= s.w[27];
    Spectrum::w[28] -= s.w[28];
    Spectrum::w[29] -= s.w[29];
    Spectrum::w[30] -= s.w[30];
#endif
}

Spectrum Spectrum::operator*(const Spectrum& s)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] * s.w[0];
    retval.w[1] = Spectrum::w[1] * s.w[1];
    retval.w[2] = Spectrum::w[2] * s.w[2];
    retval.w[3] = Spectrum::w[3] * s.w[3];
    retval.w[4] = Spectrum::w[4] * s.w[4];
    retval.w[5] = Spectrum::w[5] * s.w[5];
    retval.w[6] = Spectrum::w[6] * s.w[6];
    retval.w[7] = Spectrum::w[7] * s.w[7];
    retval.w[8] = Spectrum::w[8] * s.w[8];
    retval.w[9] = Spectrum::w[9] * s.w[9];
    retval.w[10] = Spectrum::w[10] * s.w[10];
    retval.w[11] = Spectrum::w[11] * s.w[11];
    retval.w[12] = Spectrum::w[12] * s.w[12];
    retval.w[13] = Spectrum::w[13] * s.w[13];
    retval.w[14] = Spectrum::w[14] * s.w[14];
    retval.w[15] = Spectrum::w[15] * s.w[15];
#if HQ_SPECTRUM!=0
    retval.w[16] = Spectrum::w[16] * s.w[16];
    retval.w[17] = Spectrum::w[17] * s.w[17];
    retval.w[18] = Spectrum::w[18] * s.w[18];
    retval.w[19] = Spectrum::w[19] * s.w[19];
    retval.w[20] = Spectrum::w[20] * s.w[20];
    retval.w[21] = Spectrum::w[21] * s.w[21];
    retval.w[22] = Spectrum::w[22] * s.w[22];
    retval.w[23] = Spectrum::w[23] * s.w[23];
    retval.w[24] = Spectrum::w[24] * s.w[24];
    retval.w[25] = Spectrum::w[25] * s.w[25];
    retval.w[26] = Spectrum::w[26] * s.w[26];
    retval.w[27] = Spectrum::w[27] * s.w[27];
    retval.w[28] = Spectrum::w[28] * s.w[28];
    retval.w[29] = Spectrum::w[29] * s.w[29];
    retval.w[30] = Spectrum::w[30] * s.w[30];
#endif
    return retval;

}

void Spectrum::operator*=(const Spectrum& s)
{
    Spectrum::w[0] *= s.w[0];
    Spectrum::w[1] *= s.w[1];
    Spectrum::w[2] *= s.w[2];
    Spectrum::w[3] *= s.w[3];
    Spectrum::w[4] *= s.w[4];
    Spectrum::w[5] *= s.w[5];
    Spectrum::w[6] *= s.w[6];
    Spectrum::w[7] *= s.w[7];
    Spectrum::w[8] *= s.w[8];
    Spectrum::w[9] *= s.w[9];
    Spectrum::w[10] *= s.w[10];
    Spectrum::w[11] *= s.w[11];
    Spectrum::w[12] *= s.w[12];
    Spectrum::w[13] *= s.w[13];
    Spectrum::w[14] *= s.w[14];
    Spectrum::w[15] *= s.w[15];
#if HQ_SPECTRUM!=0
    Spectrum::w[16] *= s.w[16];
    Spectrum::w[17] *= s.w[17];
    Spectrum::w[18] *= s.w[18];
    Spectrum::w[19] *= s.w[19];
    Spectrum::w[20] *= s.w[20];
    Spectrum::w[21] *= s.w[21];
    Spectrum::w[22] *= s.w[22];
    Spectrum::w[23] *= s.w[23];
    Spectrum::w[24] *= s.w[24];
    Spectrum::w[25] *= s.w[25];
    Spectrum::w[26] *= s.w[26];
    Spectrum::w[27] *= s.w[27];
    Spectrum::w[28] *= s.w[28];
    Spectrum::w[29] *= s.w[29];
    Spectrum::w[30] *= s.w[30];
#endif
}

Spectrum Spectrum::operator/(const Spectrum& s)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] / s.w[0];
    retval.w[1] = Spectrum::w[1] / s.w[1];
    retval.w[2] = Spectrum::w[2] / s.w[2];
    retval.w[3] = Spectrum::w[3] / s.w[3];
    retval.w[4] = Spectrum::w[4] / s.w[4];
    retval.w[5] = Spectrum::w[5] / s.w[5];
    retval.w[6] = Spectrum::w[6] / s.w[6];
    retval.w[7] = Spectrum::w[7] / s.w[7];
    retval.w[8] = Spectrum::w[8] / s.w[8];
    retval.w[9] = Spectrum::w[9] / s.w[9];
    retval.w[10] = Spectrum::w[10] / s.w[10];
    retval.w[11] = Spectrum::w[11] / s.w[11];
    retval.w[12] = Spectrum::w[12] / s.w[12];
    retval.w[13] = Spectrum::w[13] / s.w[13];
    retval.w[14] = Spectrum::w[14] / s.w[14];
    retval.w[15] = Spectrum::w[15] / s.w[15];
#if HQ_SPECTRUM!=0
    retval.w[16] = Spectrum::w[16] / s.w[16];
    retval.w[17] = Spectrum::w[17] / s.w[17];
    retval.w[18] = Spectrum::w[18] / s.w[18];
    retval.w[19] = Spectrum::w[19] / s.w[19];
    retval.w[20] = Spectrum::w[20] / s.w[20];
    retval.w[21] = Spectrum::w[21] / s.w[21];
    retval.w[22] = Spectrum::w[22] / s.w[22];
    retval.w[23] = Spectrum::w[23] / s.w[23];
    retval.w[24] = Spectrum::w[24] / s.w[24];
    retval.w[25] = Spectrum::w[25] / s.w[25];
    retval.w[26] = Spectrum::w[26] / s.w[26];
    retval.w[27] = Spectrum::w[27] / s.w[27];
    retval.w[28] = Spectrum::w[28] / s.w[28];
    retval.w[29] = Spectrum::w[29] / s.w[29];
    retval.w[30] = Spectrum::w[30] / s.w[30];
#endif
    return retval;
}

void Spectrum::operator/=(const Spectrum& s)
{
    Spectrum::w[0] /= s.w[0];
    Spectrum::w[1] /= s.w[1];
    Spectrum::w[2] /= s.w[2];
    Spectrum::w[3] /= s.w[3];
    Spectrum::w[4] /= s.w[4];
    Spectrum::w[5] /= s.w[5];
    Spectrum::w[6] /= s.w[6];
    Spectrum::w[7] /= s.w[7];
    Spectrum::w[8] /= s.w[8];
    Spectrum::w[9] /= s.w[9];
    Spectrum::w[10] /= s.w[10];
    Spectrum::w[11] /= s.w[11];
    Spectrum::w[12] /= s.w[12];
    Spectrum::w[13] /= s.w[13];
    Spectrum::w[14] /= s.w[14];
    Spectrum::w[15] /= s.w[15];
#if HQ_SPECTRUM!=0
    Spectrum::w[16] /= s.w[16];
    Spectrum::w[17] /= s.w[17];
    Spectrum::w[18] /= s.w[18];
    Spectrum::w[19] /= s.w[19];
    Spectrum::w[20] /= s.w[20];
    Spectrum::w[21] /= s.w[21];
    Spectrum::w[22] /= s.w[22];
    Spectrum::w[23] /= s.w[23];
    Spectrum::w[24] /= s.w[24];
    Spectrum::w[25] /= s.w[25];
    Spectrum::w[26] /= s.w[26];
    Spectrum::w[27] /= s.w[27];
    Spectrum::w[28] /= s.w[28];
    Spectrum::w[29] /= s.w[29];
    Spectrum::w[30] /= s.w[30];
#endif
}

Spectrum Spectrum::operator+(float v)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] + v;
    retval.w[1] = Spectrum::w[1] + v;
    retval.w[2] = Spectrum::w[2] + v;
    retval.w[3] = Spectrum::w[3] + v;
    retval.w[4] = Spectrum::w[4] + v;
    retval.w[5] = Spectrum::w[5] + v;
    retval.w[6] = Spectrum::w[6] + v;
    retval.w[7] = Spectrum::w[7] + v;
    retval.w[8] = Spectrum::w[8] + v;
    retval.w[9] = Spectrum::w[9] + v;
    retval.w[10] = Spectrum::w[10] + v;
    retval.w[11] = Spectrum::w[11] + v;
    retval.w[12] = Spectrum::w[12] + v;
    retval.w[13] = Spectrum::w[13] + v;
    retval.w[14] = Spectrum::w[14] + v;
    retval.w[15] = Spectrum::w[15] + v;
#if HQ_SPECTRUM!=0
    retval.w[16] = Spectrum::w[16] + v;
    retval.w[17] = Spectrum::w[17] + v;
    retval.w[18] = Spectrum::w[18] + v;
    retval.w[19] = Spectrum::w[19] + v;
    retval.w[20] = Spectrum::w[20] + v;
    retval.w[21] = Spectrum::w[21] + v;
    retval.w[22] = Spectrum::w[22] + v;
    retval.w[23] = Spectrum::w[23] + v;
    retval.w[24] = Spectrum::w[24] + v;
    retval.w[25] = Spectrum::w[25] + v;
    retval.w[26] = Spectrum::w[26] + v;
    retval.w[27] = Spectrum::w[27] + v;
    retval.w[28] = Spectrum::w[28] + v;
    retval.w[29] = Spectrum::w[29] + v;
    retval.w[30] = Spectrum::w[30] + v;
#endif
    return retval;
}

void Spectrum::operator+=(float v)
{
    Spectrum::w[0] += v;
    Spectrum::w[1] += v;
    Spectrum::w[2] += v;
    Spectrum::w[3] += v;
    Spectrum::w[4] += v;
    Spectrum::w[5] += v;
    Spectrum::w[6] += v;
    Spectrum::w[7] += v;
    Spectrum::w[8] += v;
    Spectrum::w[9] += v;
    Spectrum::w[10] += v;
    Spectrum::w[11] += v;
    Spectrum::w[12] += v;
    Spectrum::w[13] += v;
    Spectrum::w[14] += v;
    Spectrum::w[15] += v;
#if HQ_SPECTRUM!=0
    Spectrum::w[16] += v;
    Spectrum::w[17] += v;
    Spectrum::w[18] += v;
    Spectrum::w[19] += v;
    Spectrum::w[20] += v;
    Spectrum::w[21] += v;
    Spectrum::w[22] += v;
    Spectrum::w[23] += v;
    Spectrum::w[24] += v;
    Spectrum::w[25] += v;
    Spectrum::w[26] += v;
    Spectrum::w[27] += v;
    Spectrum::w[28] += v;
    Spectrum::w[29] += v;
    Spectrum::w[30] += v;
#endif
}

Spectrum Spectrum::operator-(float v)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] - v;
    retval.w[1] = Spectrum::w[1] - v;
    retval.w[2] = Spectrum::w[2] - v;
    retval.w[3] = Spectrum::w[3] - v;
    retval.w[4] = Spectrum::w[4] - v;
    retval.w[5] = Spectrum::w[5] - v;
    retval.w[6] = Spectrum::w[6] - v;
    retval.w[7] = Spectrum::w[7] - v;
    retval.w[8] = Spectrum::w[8] - v;
    retval.w[9] = Spectrum::w[9] - v;
    retval.w[10] = Spectrum::w[10] - v;
    retval.w[11] = Spectrum::w[11] - v;
    retval.w[12] = Spectrum::w[12] - v;
    retval.w[13] = Spectrum::w[13] - v;
    retval.w[14] = Spectrum::w[14] - v;
    retval.w[15] = Spectrum::w[15] - v;
#if HQ_SPECTRUM!=0
    retval.w[16] = Spectrum::w[16] - v;
    retval.w[17] = Spectrum::w[17] - v;
    retval.w[18] = Spectrum::w[18] - v;
    retval.w[19] = Spectrum::w[19] - v;
    retval.w[20] = Spectrum::w[20] - v;
    retval.w[21] = Spectrum::w[21] - v;
    retval.w[22] = Spectrum::w[22] - v;
    retval.w[23] = Spectrum::w[23] - v;
    retval.w[24] = Spectrum::w[24] - v;
    retval.w[25] = Spectrum::w[25] - v;
    retval.w[26] = Spectrum::w[26] - v;
    retval.w[27] = Spectrum::w[27] - v;
    retval.w[28] = Spectrum::w[28] - v;
    retval.w[29] = Spectrum::w[29] - v;
    retval.w[30] = Spectrum::w[30] - v;
#endif
    return retval;
}

void Spectrum::operator-=(float v)
{
    Spectrum::w[0] -= v;
    Spectrum::w[1] -= v;
    Spectrum::w[2] -= v;
    Spectrum::w[3] -= v;
    Spectrum::w[4] -= v;
    Spectrum::w[5] -= v;
    Spectrum::w[6] -= v;
    Spectrum::w[7] -= v;
    Spectrum::w[8] -= v;
    Spectrum::w[9] -= v;
    Spectrum::w[10] -= v;
    Spectrum::w[11] -= v;
    Spectrum::w[12] -= v;
    Spectrum::w[13] -= v;
    Spectrum::w[14] -= v;
    Spectrum::w[15] -= v;
#if HQ_SPECTRUM!=0
    Spectrum::w[16] -= v;
    Spectrum::w[17] -= v;
    Spectrum::w[18] -= v;
    Spectrum::w[19] -= v;
    Spectrum::w[20] -= v;
    Spectrum::w[21] -= v;
    Spectrum::w[22] -= v;
    Spectrum::w[23] -= v;
    Spectrum::w[24] -= v;
    Spectrum::w[25] -= v;
    Spectrum::w[26] -= v;
    Spectrum::w[27] -= v;
    Spectrum::w[28] -= v;
    Spectrum::w[29] -= v;
    Spectrum::w[30] -= v;
#endif
}

Spectrum Spectrum::operator*(float v)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] * v;
    retval.w[1] = Spectrum::w[1] * v;
    retval.w[2] = Spectrum::w[2] * v;
    retval.w[3] = Spectrum::w[3] * v;
    retval.w[4] = Spectrum::w[4] * v;
    retval.w[5] = Spectrum::w[5] * v;
    retval.w[6] = Spectrum::w[6] * v;
    retval.w[7] = Spectrum::w[7] * v;
    retval.w[8] = Spectrum::w[8] * v;
    retval.w[9] = Spectrum::w[9] * v;
    retval.w[10] = Spectrum::w[10] * v;
    retval.w[11] = Spectrum::w[11] * v;
    retval.w[12] = Spectrum::w[12] * v;
    retval.w[13] = Spectrum::w[13] * v;
    retval.w[14] = Spectrum::w[14] * v;
    retval.w[15] = Spectrum::w[15] * v;
#if HQ_SPECTRUM!=0
    retval.w[16] = Spectrum::w[16] * v;
    retval.w[17] = Spectrum::w[17] * v;
    retval.w[18] = Spectrum::w[18] * v;
    retval.w[19] = Spectrum::w[19] * v;
    retval.w[20] = Spectrum::w[20] * v;
    retval.w[21] = Spectrum::w[21] * v;
    retval.w[22] = Spectrum::w[22] * v;
    retval.w[23] = Spectrum::w[23] * v;
    retval.w[24] = Spectrum::w[24] * v;
    retval.w[25] = Spectrum::w[25] * v;
    retval.w[26] = Spectrum::w[26] * v;
    retval.w[27] = Spectrum::w[27] * v;
    retval.w[28] = Spectrum::w[28] * v;
    retval.w[29] = Spectrum::w[29] * v;
    retval.w[30] = Spectrum::w[30] * v;
#endif
    return retval;
}

void Spectrum::operator*=(float v)
{
    Spectrum::w[0] *= v;
    Spectrum::w[1] *= v;
    Spectrum::w[2] *= v;
    Spectrum::w[3] *= v;
    Spectrum::w[4] *= v;
    Spectrum::w[5] *= v;
    Spectrum::w[6] *= v;
    Spectrum::w[7] *= v;
    Spectrum::w[8] *= v;
    Spectrum::w[9] *= v;
    Spectrum::w[10] *= v;
    Spectrum::w[11] *= v;
    Spectrum::w[12] *= v;
    Spectrum::w[13] *= v;
    Spectrum::w[14] *= v;
    Spectrum::w[15] *= v;
#if HQ_SPECTRUM!=0
    Spectrum::w[16] *= v;
    Spectrum::w[17] *= v;
    Spectrum::w[18] *= v;
    Spectrum::w[19] *= v;
    Spectrum::w[20] *= v;
    Spectrum::w[21] *= v;
    Spectrum::w[22] *= v;
    Spectrum::w[23] *= v;
    Spectrum::w[24] *= v;
    Spectrum::w[25] *= v;
    Spectrum::w[26] *= v;
    Spectrum::w[27] *= v;
    Spectrum::w[28] *= v;
    Spectrum::w[29] *= v;
    Spectrum::w[30] *= v;
#endif
}

Spectrum Spectrum::operator/(float v)const
{
    Spectrum retval;
    retval.w[0] = Spectrum::w[0] / v;
    retval.w[1] = Spectrum::w[1] / v;
    retval.w[2] = Spectrum::w[2] / v;
    retval.w[3] = Spectrum::w[3] / v;
    retval.w[4] = Spectrum::w[4] / v;
    retval.w[5] = Spectrum::w[5] / v;
    retval.w[6] = Spectrum::w[6] / v;
    retval.w[7] = Spectrum::w[7] / v;
    retval.w[8] = Spectrum::w[8] / v;
    retval.w[9] = Spectrum::w[9] / v;
    retval.w[10] = Spectrum::w[10] / v;
    retval.w[11] = Spectrum::w[11] / v;
    retval.w[12] = Spectrum::w[12] / v;
    retval.w[13] = Spectrum::w[13] / v;
    retval.w[14] = Spectrum::w[14] / v;
    retval.w[15] = Spectrum::w[15] / v;
#if HQ_SPECTRUM!=0
    retval.w[16] = Spectrum::w[16] / v;
    retval.w[17] = Spectrum::w[17] / v;
    retval.w[18] = Spectrum::w[18] / v;
    retval.w[19] = Spectrum::w[19] / v;
    retval.w[20] = Spectrum::w[20] / v;
    retval.w[21] = Spectrum::w[21] / v;
    retval.w[22] = Spectrum::w[22] / v;
    retval.w[23] = Spectrum::w[23] / v;
    retval.w[24] = Spectrum::w[24] / v;
    retval.w[25] = Spectrum::w[25] / v;
    retval.w[26] = Spectrum::w[26] / v;
    retval.w[27] = Spectrum::w[27] / v;
    retval.w[28] = Spectrum::w[28] / v;
    retval.w[29] = Spectrum::w[29] / v;
    retval.w[30] = Spectrum::w[30] / v;
#endif
    return retval;
}

void Spectrum::operator/=(float v)
{
    Spectrum::w[0] /= v;
    Spectrum::w[1] /= v;
    Spectrum::w[2] /= v;
    Spectrum::w[3] /= v;
    Spectrum::w[4] /= v;
    Spectrum::w[5] /= v;
    Spectrum::w[6] /= v;
    Spectrum::w[7] /= v;
    Spectrum::w[8] /= v;
    Spectrum::w[9] /= v;
    Spectrum::w[10] /= v;
    Spectrum::w[11] /= v;
    Spectrum::w[12] /= v;
    Spectrum::w[13] /= v;
    Spectrum::w[14] /= v;
    Spectrum::w[15] /= v;
#if HQ_SPECTRUM!=0
    Spectrum::w[16] /= v;
    Spectrum::w[17] /= v;
    Spectrum::w[18] /= v;
    Spectrum::w[19] /= v;
    Spectrum::w[20] /= v;
    Spectrum::w[21] /= v;
    Spectrum::w[22] /= v;
    Spectrum::w[23] /= v;
    Spectrum::w[24] /= v;
    Spectrum::w[25] /= v;
    Spectrum::w[26] /= v;
    Spectrum::w[27] /= v;
    Spectrum::w[28] /= v;
    Spectrum::w[29] /= v;
    Spectrum::w[30] /= v;
#endif
}

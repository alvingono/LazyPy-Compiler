# Sofia Example 6
 def main():
    long_text = """
    Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum vitae urna ligula. Nulla facilisi.
    Proin tincidunt neque ac mi consequat, nec volutpat purus fringilla. Nam consectetur sem vel lorem 
    dignissim, a feugiat felis sodales. Suspendisse potenti. In facilisis viverra libero, ut vehicula odio 
    aliquet ut. Aenean a venenatis velit, sed fermentum nisl. Donec sed arcu at est pellentesque venenatis 
    id sed justo. Sed condimentum, turpis nec cursus dapibus, justo diam sodales justo, nec faucibus dolor 
    dolor vitae purus. Nullam a consectetur ipsum. Quisque in purus lectus.

    Aenean mollis massa sit amet sapien pharetra, at vehicula justo auctor. Vivamus sodales vehicula diam. 
    Nam consequat libero at tortor iaculis, eu laoreet libero fringilla. Cras semper ullamcorper lacus, sed 
    pulvinar ligula vehicula et. Nulla facilisi. Mauris pretium, tortor in finibus congue, tortor ante 
    accumsan odio, eu ultricies ligula sem id libero. Suspendisse consectetur tortor ut vehicula sodales. 
    Praesent at urna euismod, sodales sem sed, dictum felis. Aenean ut sem nec lorem bibendum vehicula. 

    Nullam quis sapien at sem vehicula scelerisque ut non est. Nullam sit amet ex a nulla scelerisque auctor. 
    Vivamus condimentum posuere libero vel vehicula. Nullam vulputate massa eget ex ullamcorper, vitae 
    convallis eros lobortis. Morbi tincidunt et metus a dapibus. Proin ut justo magna. Cras vitae libero 
    eget libero vulputate posuere. Suspendisse potenti. Cras non turpis feugiat, posuere orci vel, fermentum 
    urna. Mauris eget ante tortor. In vel felis id eros finibus blandit. Nullam ac facilisis arcu.

    Vivamus quis sollicitudin odio, ac auctor leo. Aliquam erat volutpat. Donec pulvinar eros nisi, ac 
    varius ligula convallis sit amet. Curabitur cursus scelerisque semper. Nullam lacinia, leo in dictum 
    dapibus, dui metus laoreet sapien, in tincidunt lectus elit ac erat. Sed euismod eros id lectus 
    ultricies, eget laoreet sem egestas. Maecenas vehicula ligula a nunc scelerisque, ac bibendum sem 
    aliquet. Vestibulum fermentum orci a sagittis venenatis. Duis consequat interdum ex ut consequat.

    Ut a suscipit risus. In venenatis mollis dapibus. Aliquam et lacus suscipit, efficitur orci at, tempor 
    odio. Nam vulputate scelerisque felis, eget pharetra purus venenatis sit amet. Donec euismod urna non 
    erat vehicula, sit amet aliquam felis fringilla. Sed dictum est a libero vulputate sodales. Aliquam 
    scelerisque urna nec lectus consectetur, ut ultricies mauris lacinia. Nam dignissim fermentum nulla, sed 
    pharetra arcu luctus at. Quisque vel semper lectus. Aliquam pellentesque vehicula enim. Donec lacinia 
    venenatis dui, a viverra odio accumsan eget. Sed quis sem euismod, volutpat metus id, vehicula dui. 

    Curabitur nec libero at sem molestie ultricies. Sed fringilla est id magna aliquam, et lobortis lacus 
    bibendum. Aenean posuere scelerisque odio, vitae interdum justo. Proin a erat id elit faucibus 
    scelerisque at a libero. Integer mollis odio nec diam cursus, non scelerisque lacus rhoncus. Ut feugiat, 
    justo sed bibendum tincidunt, urna nunc laoreet magna, sit amet auctor purus lectus eget sapien. Nulla 
    facilisi. Sed ac nisl sed ante venenatis vestibulum. Nam faucibus lacus velit, sed molestie felis 
    maximus et. Nulla pellentesque sapien a interdum accumsan.

    Suspendisse potenti. Quisque id sollicitudin nibh, vel fermentum libero. Nullam ac lacus tristique, 
    porttitor purus et, viverra orci. Sed non nisi dolor. Phasellus tincidunt libero non rhoncus cursus. 
    Nullam vitae nulla orci. Nullam vel urna in felis elementum vehicula. Integer tincidunt lorem ac tortor 
    volutpat, non interdum justo pulvinar. Donec elementum sem vitae risus condimentum dictum. Duis 
    accumsan, sapien at dapibus rhoncus, quam ante commodo odio, non mollis felis augue ut lorem. 
    Pellentesque dictum bibendum convallis.

    Nam gravida sagittis dui, at sagittis sem suscipit sit amet. Vivamus pellentesque nisl non orci 
    scelerisque, vel hendrerit nisl vehicula. Vestibulum tincidunt feugiat dolor. Maecenas facilisis lacus 
    eros. Integer consectetur, velit a volutpat pellentesque, nulla libero dapibus ligula, a venenatis neque 
    lorem a justo. Suspendisse euismod justo quis nibh dictum hendrerit. Aliquam erat volutpat. Proin quis 
    metus ac nisi volutpat suscipit ut id nisl. Fusce ut erat quis enim fringilla auctor. Pellentesque vel 
    metus nec velit venenatis vehicula. Nunc ullamcorper magna ex, id tincidunt elit vehicula a. Proin 
    fringilla, nunc in laoreet efficitur, dolor erat rutrum est, vitae posuere sem magna nec risus. Nulla 
    eget turpis urna. Vivamus vel metus et orci laoreet gravida in sed libero.

    Maecenas id vestibulum ante. Nullam tincidunt euismod felis, ut fringilla lectus molestie ac. Integer a 
    odio et nisi mollis feugiat. Vivamus id nisl id mauris vestibulum molestie. Morbi vestibulum augue sit 
    amet dignissim maximus. Nam dignissim, ex eget interdum faucibus, turpis augue tempor lectus, in gravida 
    velit sapien ut libero. Fusce volutpat feugiat nisl non dignissim. Morbi tristique, tortor non molestie 
    vehicula, nisi nunc fringilla ipsum, eget gravida ipsum felis eget urna. Curabitur vitae dui enim. Ut 
    suscipit massa a gravida blandit.

    In ut arcu sit amet odio posuere scelerisque. Morbi eget dapibus ex, et porttitor eros. Vestibulum ante 
    ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Vestibulum pharetra lectus sed 
    nisl vehicula, vel efficitur magna fermentum. Proin aliquam gravida eros nec finibus. Maecenas hendrerit 
    metus ut neque dictum tempor. Proin eget sagittis ex, non pretium lorem. Quisque non scelerisque erat. 
    Nam sit amet velit dui. Suspendisse at vehicula nibh. Mauris a vehicula ex. Nunc non odio euismod, 
    volutpat quam at, lobortis turpis. Praesent sodales purus sit amet luctus tristique. Vestibulum 
    consectetur justo ut auctor consectetur. Sed faucibus arcu quam, eu bibendum sem dictum nec.

    Aliquam non ultricies felis, eget vehicula ante. Duis vestibulum, nunc sit amet laoreet posuere, est est 
    scelerisque felis, a aliquam tortor ligula vitae dolor. Curabitur id sapien fringilla, bibendum urna 
    quis, varius massa. Donec sagittis libero nec justo consectetur, eget bibendum dolor interdum. Quisque 
    dignissim tristique orci, eu tempor ex tempor vel. Mauris sollicitudin velit euismod nulla volutpat 
    interdum. Fusce non risus nec est suscipit bibendum. Suspendisse sit amet consectetur erat, ut maximus 
    quam. Sed vitae lobortis ex, a luctus enim. Aenean accumsan iaculis tempor. Suspendisse vitae lacus 
    aliquam, blandit est eu, dignissim neque. Nunc pharetra massa sed lectus laoreet gravida. Proin id nulla 
    eros. Morbi sagittis sapien sit amet risus rutrum blandit. Duis efficitur mi a enim tempus, ut varius 
    nunc tincidunt. Vestibulum ultricies libero eu ligula vestibulum, eu hendrerit risus pellentesque.

    Integer dapibus felis ac odio fermentum, eget tempus dolor aliquet. Fusce vehicula sapien velit, eu 
    scelerisque lorem viverra a. Curabitur sodales, justo ut auctor dapibus, risus orci dignissim neque, nec 
    faucibus orci eros non nisi. Donec sit amet massa mi. Vestibulum ante ipsum primis in faucibus orci 
    luctus et ultrices posuere cubilia curae; Pellentesque convallis vestibulum dolor, sed finibus nulla 
    consequat eu. Donec mollis nisl vel tortor lobortis tristique. Vivamus eget dui leo. Sed tempor cursus 
    arcu, nec rutrum purus fermentum vel. Integer libero sem, feugiat et auctor nec, tincidunt vel tortor. 

    Suspendisse ultricies facilisis risus, ut vulputate ligula congue in. Morbi sed neque risus. Praesent 
    scelerisque nisi vitae turpis tincidunt malesuada. Donec vitae fermentum nisi, ut venenatis metus. Sed 
    sed ornare dui. Integer gravida est et nulla hendrerit, non lacinia felis vestibulum. In ac nisi in 
    augue convallis tincidunt at non arcu. Vivamus convallis elit leo, eget efficitur nisl hendrerit ut. 
    Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Duis eu 
    malesuada ante, sed facilisis nunc. Pellentesque semper magna nec mauris auctor ultricies. Donec et nunc 
    at dolor scelerisque bibendum id a lacus. Sed pellentesque nulla quis enim malesuada, a porttitor lorem 
    ornare. Ut porttitor sodales facilisis. Morbi scelerisque placerat turpis, in iaculis metus vestibulum 
    nec.

    Donec sagittis felis sit amet cursus feugiat.


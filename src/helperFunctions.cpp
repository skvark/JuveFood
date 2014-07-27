#include <QByteArray>
#include <QString>

/* This method fixes the invalid JSON data which Juvenes API offers.
 * It's not pretty but has to be done.
 * Cleans dirty QByteArray so that it can be read to QJsonDocument.
 */
void cleanJSON(QByteArray &dirty, bool isInfo) {

    if(!isInfo) {
       // remove "}); from the end
       dirty.remove(dirty.length() - 4, 4);
       // remove ({"d":" from the beginning
       dirty.remove(0, 7);

       // Juvenes API is eh.. broken.
       // It's better you don't even try to think what
       // these lines of code do. Really, just go away.

       const char* remove = "\\\\\\\"";
       const char* replace = "";
       dirty.replace(remove, replace);

       remove = "\\\"";
       replace = "\"";
       dirty.replace(remove, replace);

       remove = "\\u003cbr\\\\/\\u003e";
       replace = " ";
       dirty.replace(remove, replace);

    } else {
        // remove "); from the end
        dirty.remove(dirty.length() - 2, 2);
        // remove ({"d":" from the beginning
        dirty.remove(0, 1);
    }
}

QString cleanOpeningHours(QString dirty) {
    QByteArray utf8string = dirty.toUtf8();
    utf8string.replace("\\\"", "\"");
    utf8string.replace("\\/", "/");
    utf8string.replace("\\u000a", "");
    utf8string.replace("\"<", "<");
    utf8string.replace(">\"", ">");
    return QString::fromUtf8(utf8string);
}


// Shortens the restaurant names by stripping obsolete information
void nameCompactor(const QString& name, QString& shortName){

    // Split into restaurant name and a specifier (such as "Fusion kitchen")
    int end = name.indexOf(" -") - 1;
    if(end == -2){
        // name is in an unknown format, do nothing.
        shortName = name;
        return;
    } else if (end == -1) {
        // not found
        shortName = name;
        return;
    }
    int begin = name.lastIndexOf(' ', end) + 1;
    if(name[begin].isLower()){
        // Name consists of several words
        shortName = name.left(end + 1);
    }else{
        // Single word name
        shortName = name.mid(begin, end - begin + 1);
    }

    // Check if non-trivial specifier is present
    if(!name.contains("Lounas")){
        if(name.contains("Fusion")){
            shortName += " - Fusion";
        }else{
            shortName += name.mid(end + 1);
        }
    }
}

#ifndef SCRIPT_H
#define SCRIPT_H

#endif // SCRIPT_H

#include <QColor>
#include <QString>
#include <QFont>
#include <QFile>

const int NO_ERROR = 0;
const int IMAGE_OPENENING_ERROR = 1;
const int PAINTER_BEGINNIG_ERROR = 2;
const int IMAGE_SAVING_ERROR = 3;

bool GenerateDiploma(const QString& background, const QString& text, int x, int y, const QColor&, const QFont& font,const QString& folder,  const QString& result_name, int* error = nullptr);
QString erToString(int er);

bool getLine(QFile& file, QString& str);

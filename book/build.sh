#!/bin/sh
srcDir="../src"
srcFiles=$(ls ${srcDir})
buildDir="../book/src/autodoc"
tableOfContentsFile=$buildDir/table_of_contents.md

_genTableOfContents()
{
	echo "# Birb2D functions" > $tableOfContentsFile
	echo "This file is generated automatically. Please don't modify it, it will be overwritten." >> $tableOfContentsFile
	echo "## Files" >> $tableOfContentsFile
}

# Create the build target directory if it doesn't exist already
[ -d $buildDir ] || mkdir -p $buildDir

# Create table of contents file
_genTableOfContents

_addFileToTableOfContents()
{
	file=$1
	fileName=$2
	touch $buildDir/$fileName.md
	echo "* [${fileName^}](./$fileName.md)" >> $tableOfContentsFile
}

echo "> Looking for documentation function comments..."
for i in $srcFiles
do
	fileName=$(basename $i | cut -d'.' -f1)
	mdfile=$buildDir/$fileName.md
	echo "# ${fileName^}" > $mdfile
	grep -A 1 "//\*\*" ${srcDir}/${i} | sed 's|//\*\* ||g' | ./autodoc/autodoc >> $mdfile && _addFileToTableOfContents $i $fileName
done

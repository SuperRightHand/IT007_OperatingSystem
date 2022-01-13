var FramesNumber = document.getElementsByName('FramesNumber');
var Pages = document.getElementsByName('Pages');
var Algorithm = document.getElementsByName('Algorithm');

var Frames = [];
var PageFault = [];
var PositionFault = [];


function CreateValues(array) {
    return array.value;
}
function countPage(indexPage) {
    for (let index = 0; index < indexPage.length; index++) {
        indexPage[index]++;
    }
}

function SelectRow(indexPage, FramesNumberValue) {
    var max = indexPage[0];
    var selection = 0;
    for (let index = 0; index < FramesNumberValue; index++) {
        if (indexPage[index] > max)
        {
            max = indexPage[index];
            selection = index;
        }
    }
    return selection;
}

function CheckValueInTable(PageArray, FramesNumberValue, columnCurrent) {
    for (let index = 0; index < FramesNumberValue; index++) {
        if (PageArray == Frames[columnCurrent][index]) return false;
    }
    return true;
}

function selectRowOPT(FramesNumberValue, PagesArray, ColumnCurrent) {
    var max = -1;
    var selection = 0;
    for (let index = 0; index < FramesNumberValue; index++)
    {
        for (let i = ColumnCurrent + 1; i < PagesArray.length; i++)
        {
            if (Frames[ColumnCurrent][index] == Number(PagesArray[i]))
            {
                if(i > max)
                {
                    selection = index;
                    max = i;
                }
                break;
            }
            else if (i == PagesArray.length - 1) {
                selection = index;
                max = PagesArray.length;
            }
        }
        if (max == PagesArray.length) break;
    }
    for (let index = 0; index < FramesNumberValue; index++) {
        if (Frames[ColumnCurrent][index] == undefined || Frames[ColumnCurrent][index] == -1) {
            selection = index;
            break;
        }
    }
    return selection;
}

function SelectPositionLRU(PageArray, FramesNumberValue, columnCurrent) {
    for (let index = 0; index < FramesNumberValue; index++) {
        if (PageArray == Frames[columnCurrent][index]) return index;
    }
}

function Process() {
    var FramesNumberValue = CreateValues(FramesNumber[0]);
    for (var i = 0; i < FramesNumberValue; i++) Frames.push([]);
    Frames[0]=[-1];
    var PagesValue = CreateValues(Pages[0]);
    var AlgorithmValue = CreateValues(Algorithm[0]);

    var PagesArray = PagesValue.split("");
    switch (AlgorithmValue) {
        case 'FIFO':
            FIFOfunction(FramesNumberValue, PagesArray);
            CheckPageFault(FramesNumberValue);
            DeleteTable();
            CreateTable(FramesNumberValue, PagesArray);
            break;
        case 'OPT':
            OPTfunction(FramesNumberValue, PagesArray);
            CheckPageFault(FramesNumberValue);
            DeleteTable();
            CreateTable(FramesNumberValue, PagesArray);
            break;
        case 'LRU':
            LRUfunction(FramesNumberValue, PagesArray);
            CheckPageFault(FramesNumberValue);
            DeleteTable();
            CreateTable(FramesNumberValue, PagesArray);
            break;
        case '3':
            FIFOfunction(FramesNumberValue, PagesArray);
            CheckPageFault(FramesNumberValue);
            DeleteTable();
            CreateTable(FramesNumberValue, PagesArray);
            OPTfunction(FramesNumberValue, PagesArray);
            CheckPageFault(FramesNumberValue);
            CreateTable(FramesNumberValue, PagesArray);
            LRUfunction(FramesNumberValue, PagesArray);
            CheckPageFault(FramesNumberValue);
            CreateTable(FramesNumberValue, PagesArray);
            break;
        default:
            break;
    }
}

function FIFOfunction(FramesNumberValue, PagesArray) {
    var indexPage = [];
    for (var index = 0; index < FramesNumberValue; index++) indexPage[index] = 0;
    var lengthPages = PagesArray.length;
    for (var index = 0; index < lengthPages; index++)
    {
        countPage(indexPage);
        if (index) Frames[index] = [...Frames[index-1]];
        if (CheckValueInTable(Number(PagesArray[index]), FramesNumberValue, index))
        {
            var i = SelectRow(indexPage, FramesNumberValue);
            Frames[index][i] = Number(PagesArray[index]);
            indexPage[i] = 0;
        }
    }
}

function LRUfunction(FramesNumberValue, PagesArray) {
    var indexPage = [];
    for (var index = 0; index < FramesNumberValue; index++) indexPage[index] = 0;
    var lengthPages = PagesArray.length;
    for (var index = 0; index < lengthPages; index++)
    {
        countPage(indexPage);
        if (index) Frames[index] = [...Frames[index-1]];
        if (CheckValueInTable(Number(PagesArray[index]), FramesNumberValue, index))
        {
            var i = SelectRow(indexPage, FramesNumberValue);
            Frames[index][i] = Number(PagesArray[index]);
            indexPage[i] = 0;
        }
        else
        {
            var i = SelectPositionLRU(Number(PagesArray[index]), FramesNumberValue, index);
            indexPage[i] = 0;
        }
    }
}

function OPTfunction(FramesNumberValue, PagesArray) {
    var lengthPages = PagesArray.length;
    for (var index = 0; index < lengthPages; index++)
    {
        if (index) Frames[index] = [...Frames[index-1]];
        if (CheckValueInTable(Number(PagesArray[index]), FramesNumberValue, index))
        {
            var i = selectRowOPT(FramesNumberValue, PagesArray, index);
            Frames[index][i] = Number(PagesArray[index]);
        }
    }
}

function CheckPageFault(FramesNumberValue) {
    PageFault[0] = 1;
    PositionFault[0] = 0;
    for (let index = 1; index < Frames.length; index++) {
        PageFault[index] = 0;
        PositionFault[index] = -1;
        for (let i = 0; i < FramesNumberValue; i++) {
            if (Frames[index-1][i] != Frames[index][i]) {
                PageFault[index] = 1;
                PositionFault[index] = i;
                break;
            }
        }
    }
}

function CreateTable(FramesNumberValue, PagesArray) {
    var table = document.getElementById('myTable');
    var header = table;
    var rowHeader = header.insertRow();
    var cellHeader = rowHeader.insertCell();
    for (let index = 0; index < PagesArray.length; index++) {
        cellHeader = rowHeader.insertCell();
        cellHeader.innerHTML = PagesArray[index];
    }
    for (let index = 0; index < FramesNumberValue; index++) {
        var row = table.insertRow();
        var cell = row.insertCell();
        cell.innerHTML = index + 1;
        for (let i = 0; i < PagesArray.length; i++) {
            cell = row.insertCell();
            if (Frames[i][index] != undefined) cell.innerHTML = Frames[i][index];
            if (PositionFault[i] == index) cell.style.backgroundColor = 'yellow';
        }
    }
    var rowFooter = table.insertRow();
    var cellFooter = rowFooter.insertCell();
    cellFooter.innerHTML = 'Page Fault';
    for (let i = 0; i < PagesArray.length; i++) {
        cellFooter = rowFooter.insertCell();
        if (PageFault[i]) cellFooter.innerHTML = 'x';
    }
    var sum = 0;
    for (let index = 0; index < PagesArray.length; index++) {
        sum+=PageFault[index];
    }
    cellFooter = rowFooter.insertCell();
    cellFooter.innerHTML = sum;
    cellFooter.style.backgroundColor = 'red';
}

function DeleteTable() {
    var currentTable = document.querySelector('tbody');
    console.log(currentTable);
    if (currentTable) currentTable.remove();
}
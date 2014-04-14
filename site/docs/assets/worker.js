/**
 * @constructor
 */
function Ultra(rootURL) {
	this.root = rootURL;
}

/**
 * @constructor
 */
createXMLHttpRequest = function() {
   try { return new XMLHttpRequest(); } catch(e) {}
   try { return new ActiveXObject("Msxml2.XMLHTTP"); } catch (e) {}
   sgxError("XMLHttpRequest not supported - you can not retrieve external data files");
   return null;
}
 
Ultra.prototype.get = function(url, cbfn) {
	
	this.getrequest=new createXMLHttpRequest();
	
	var thisGetRequest = this.getrequest;
	var thisFile = this;
	this.getrequest.onreadystatechange=function(){
	        if (thisGetRequest['readyState']==4){
	                if (thisGetRequest['status']==200){
	                	cbfn && cbfn != undefined && cbfn(thisGetRequest['responseText']);
	                        //thisFile.close();
	                } else {        // even from  local, i.e. window.location.href.indexOf("http")==-1
	                       // thisFile.onFileOpenFailed(thisFile);
	                }
	        }
	};
	
	try {   
	        this.getrequest.open("GET", url, true)
	        this.getrequest.send(null);
	} catch(e) {
	        //thisFile.onFileOpenFailed(thisFile);
	}

}

Ultra.prototype.getData = function(dbField, cbfn) {
	var url = "db/" + dbField;
	this.get(url, cbfn);	
}



/*
var u  = new Ultra("http://localhost:8088/");
u.get("two.htm");
u.get("one.htm", function(data) { alert(data); });

u.get("db.user.3.name", function(data) { alert(data); });
*/



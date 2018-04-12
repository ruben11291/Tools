#### Author: Ruben Perez Pascual
#### Email: ruben11291@gmail.com
################################

import json
import requests
from collections import Counter

desiredKeys = ['id', 'state', 'title', 'repository', 'created_at']


def get_github_issue (owner , name):
    url = 'https://api.github.com/repos/%s/%s/issues' % (owner ,name)
    return requests.get(url)

def jsonizer_issue(issues):
    ret = []
    list_issues = json.loads(issues.text)
    for issue in json.loads(issues.text):
        ret.append ( { k:v for k,v in issue.items() if k in desiredKeys } )
    return ret

    

def createTopDay (repos):
    created_at = dict()
    for repo in repos:
        for issue in repos[repo]:#['issues']:
            key =issue['created_at']
            if not created_at.has_key(key):
                created_at[key] = []
            created_at[key].append(repo)
    return created_at


def selectTopDay( tops ):
    ref = None
    count = 0
    b = tops.items()
    import pdb
    pdb.set_trace()
    for date, repos in sorted(tops.items(),reverse=True):
        if len(repos) > count: #it will always allocate last date because tops is ordered
            ref = [date,Counter(repos).items()]
            count = len(repos)
    return ref



if __name__ == '__main__':
    import sys
    repos = dict()
    report = dict()
    if len(sys.argv) >1:
        for pair in sys.argv[1:]:
            if not repos.has_key(pair):
                #final_dict = dict()
                #final_dict['top-day']= dict()
                #final_dict['issues'] = jsonizer_issue( get_github_issue(pair.split("/")[0], pair.split("/")[1]) )
                final_dict = jsonizer_issue( get_github_issue(pair.split("/")[0], pair.split("/")[1]) )
                sorted ( final_dict , key = lambda date: date['created_at'] ) #sorting
                repos[pair] = final_dict
                #print repos[pair]
        report['issues'] = repos
        report['top-day']= selectTopDay (createTopDay(repos) )
        print json.dumps(report)
    else:
        print ("At least a repo and owner must be introduced (Format owner/name)")

    
